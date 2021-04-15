# 智能指针

## 使用智能指针的目的

### 避免野指针，设想两个场景：

- ptr 指向对象A，对A使用结束后主动delete A，但未置ptr为空。如果有第三方应用试图用ptr访问A，首先会判断ptr是否为空，由于未置ptr为nullptr，故此判断为true，然后通过ptr操作不存在的A，自然出错。
- ptr1和ptr2均指向A，通过ptr1 释放 A的内存后，将ptr1置为nullptr。当用ptr2访问A时，首先判断ptr2是否为空，由于不为空，故用ptr2访问A，但实际上A不存在，导致ptr2访问A出错。

## 引用计数类LightRefBase

若一个类想拥有智能指针的功能，它必须继承一个统一的父类LightRefBase，以满足引用计数功能。

```c++
// frameworks/base/include/utils/RefBase.h
template <class T>
class LightRefBase
{
public:
    inline LightRefBase() : mCount(0) { }
    inline void incStrong(const void* id) const { 
        android_atomic_inc(&mCount); // 原子操作，增加引用计数
    }
    // 原子操作，减少引用计数
    inline void decStrong(const void* id) const {
        // 若引用计数的旧值是1，则释放该对象内存；否则，只是正常的减少引用计数
        if (android_atomic_dec(&mCount) == 1) {  
            // 由于在应用时会有某一个具体的类继承LightRefBase，故释放的是该具体类
            delete static_cast<const T*>(this);
        }
    }
    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() const {
        return mCount;
    }

    typedef LightRefBase<T> basetype;

protected:
    inline ~LightRefBase() { }

private:
    /**
     * 当要求使用 volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，
     * 即使它前面的指令刚刚从该处读取过数据
     */
    mutable volatile int32_t mCount; 
};
```

## 强指针

强指针实现C++11 shared_ptr的功能，Android中的sp指针与std::shared_ptr的区别参考

[Android native strong pointer vs std::shared_ptr](https://stackoverflow.com/questions/42142375/android-native-strong-pointer-vs-stdshared-ptr)

```c++
// frameworks/base/include/utils/StrongPointer.h
template <typename T>
class sp
{
public:
    inline sp() : m_ptr(0) { } //默认指向空

    sp(T* other);
    sp(const sp<T>& other);

    ~sp();

    // Assignment
    // 重载赋值运算符
    sp& operator = (T* other); 
    sp& operator = (const sp<T>& other);
    
    inline  T&      operator* () const  { return *m_ptr; } // 重载解引用(*)运算符
    inline  T*      operator-> () const { return m_ptr;  } // 重载指针(->)运算符
    inline  T*      get() const         { return m_ptr; }

    // 比智能指针间的比较操作，不分析

private:    
    T* m_ptr;
};
```

### 构造函数

```c++
// 将普通指针处理为智能指针
template<typename T>
sp<T>::sp(T* other)
: m_ptr(other)
  {
    if (other) other->incStrong(this);
  }

// 智能指针间相互赋值，让另一个智能指针和它指向同一个对象
template<typename T>
sp<T>::sp(const sp<T>& other)
: m_ptr(other.m_ptr)
  {
    if (m_ptr) m_ptr->incStrong(this);
  }
```

### 析构函数

```c++
// 析构该智能指针，只是让智能指针指向的对象的引用计数减一。
// 当减一后引用计数变为0，最终会调用 delete static_cast<const T*>(this)，参考LightRefBase
template<typename T>
sp<T>::~sp()
{
    if (m_ptr) m_ptr->decStrong(this);
}
```

### 重载赋值运算

```c++
// 让一个智能指针重新指向另一个智能指针other指向的对象
template<typename T>
sp<T>& sp<T>::operator = (const sp<T>& other) {
    T* otherPtr(other.m_ptr);
    // 又有一个新的智能指针指向该对象，故该对象的引用计数加一
    if (otherPtr) otherPtr->incStrong(this);
    // 由于该智能指针指向了other指向的对象，故不能指向它之前指向的对象，所以之前指向的对象引用计数减一 
    if (m_ptr) m_ptr->decStrong(this);
    // 该智能指针现在应指向other指向的对象
    m_ptr = otherPtr;
    return *this;
}

// 让一个智能指针指向一个普通指针other所指向的对象
template<typename T>
sp<T>& sp<T>::operator = (T* other)
{
    if (other) other->incStrong(this);
    if (m_ptr) m_ptr->decStrong(this);
    m_ptr = other;
    return *this;
}
```

## 弱指针

简单总结为什么需要弱指针：

**弱指针存在的目的就是为了解决循环引用的现象。**

设想一个场景，父类Dad用强指针指向子类Child，子类Child用强指针指向父类Dad，则两者的引用计数均不为0，此时两者的内存都将不会得到释放。因此需要采用弱引用，**即父类可以用强指针指向子类，子类只能用弱指针指向父类，以避免循环引用。**

规定：

- 当强指针引用计数为0时，无论弱指针的引用计数为多少，对象均可以delete自己。只要一方得到了释放，另一方也就可以释放。

- 弱指针必须先升级为强指针，才可以访问它指向的目标对象。

  **为何**？沿用上面的情况，设父类的强指针引用为0，它释放自己；而子类还持有父类的弱引用，如果弱引用可以访问它所指向的目标对象即父类，自然会出错，因此规定弱引用不可直接访问它指向的目标对象。





