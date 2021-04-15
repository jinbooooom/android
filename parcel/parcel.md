```java
// frameworks/base/core/java/android/os/Parcel.java
private static final int POOL_SIZE = 6;
private static final Parcel[] sOwnedPool = new Parcel[POOL_SIZE]
    
/**
* Retrieve a new Parcel object from the pool.
*/
public static Parcel obtain() {
    final Parcel[] pool = sOwnedPool;
    synchronized (pool) {
        Parcel p;
        for (int i=0; i<POOL_SIZE; i++) {
            p = pool[i];
            if (p != null) {
                pool[i] = null;
                if (DEBUG_RECYCLE) {
                    p.mStack = new RuntimeException();
                }
                return p;
            }
        }
    }
    return new Parcel(0);
}
```

