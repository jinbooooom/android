# 内容录制

### 指明支持录制

在录制之前应告知系统支持录制。

**方法一：**

将您的服务元数据 XML 文件中的 `android:canRecord` 属性设置为 `true`：

```xml
<tv-input xmlns:android="http://schemas.android.com/apk/res/android"
      android:canRecord="true"
      android:setupActivity="com.example.sampletvinput.SampleTvInputSetupActivity" />
```

**方法二：**

在代码中指明支持录制。

1. 在 TV 输入服务 `onCreate()` 方法中，使用 `TvInputInfo.Builder` 类创建一个新的 `TvInputInfo` 对象。
2. 创建新的 `TvInputInfo` 对象时，在调用 `build()` 之前先调用 `setCanRecord(true)`，以指明您的服务支持录制。
3. 通过调用 `TvInputManager.updateTvInputInfo()` 在系统中注册 `TvInputInfo` 对象。

---

- `public void onCreate ()`：首次创建服务时由系统调用。 不要直接调用此方法。

- `TvInputInfo`：用于指定电视输入的源信息。
  
- `public TvInputInfo build ()`：用指定的字段创建一个`TvInputInfo`实例。
  
- `TvInputInfo.Builder`：用于创建`TvInputInfo`对象的便捷构建器。
  
- ` public TvInputInfo.Builder setCanRecord (boolean canRecord)`：设置`TV`是否支持录制。
  
- `TvInputManager`：总体电视输入框架（TIF）架构的中央系统API，可仲裁应用程序与选定电视输入之间的交互。

  电视输入框架（TIF）架构涉及三个主要方面：

  1.此类表示的“电视输入管理器”是管理所有其他部分之间的交互的系统的中心点。它在此处表示为客户端`API`，存在于每个应用程序上下文中，并与管理所有进程之间的交互的全局系统服务进行通信。

  2.由`TvInputService`实现的“电视输入”表示电视的输入源，可以是诸如`HDMI`之类的直通输入，也可以是提供广播电视节目的调谐器输入。系统根据每个应用程序的请求绑定到电视输入。关于实施电视输入。

  3.应用程序与电视输入管理器对话，以列出电视输入并检查其状态。 一旦应用程序找到要使用的输入，它将使用TvView或TvRecordingClient进行进一步的交互，例如观看和录制广播电视节目。

- `TvInputManager.updateTvInputInfo()` :更新现有电视输入的`TvInputInfo`。 电视输入服务的实现可以调用此方法以将应用程序和系统传递给描述其自身的最新`TvInputInfo`对象。

  系统会根据从`AndroidManifest.xml`收集的信息为每个电视输入自动创建一个`TvInputInfo`对象，因此，除非此类信息已动态更改，否则无需调用此方法。 使用`TvInputInfo.Builder`生成一个新的`TvInputInfo`对象。

### 录制会话

> TV 输入服务注册其支持录制功能后，系统会在需要访问应用的录制实现时调用 `TvInputService.onCreateRecordingSession()` 方法。**实现您自己的 `TvInputService.RecordingSession` 子类并在触发 `onCreateRecordingSession()` 回调后返回它。**此子类**负责切换到正确的频道数据，录制请求的数据，以及向系统传达录制状态和错误**。
>
> 系统调用在频道 URI 中传递的 `RecordingSession.onTune()` 时，**将调到该 URI 指定的频道**。通过调用 `notifyTuned()` 通知系统应用已调到所需的频道，或者，如果应用无法调到正确的频道，请调用 `notifyError()`。
>
> 接下来系统会调用 `RecordingSession.onStartRecording()` 回调。您的应用必须立即开始录制。系统调用此回调时，它可能会提供一个 URI，其中包含有关即将录制的节目的信息。录制完成后，您需要将此数据复制到 `RecordedPrograms` 数据表。
>
> 最后，系统会调用 `RecordingSession.onStopRecording()`。此时，您的应用必须立即停止录制。您还需要在 `RecordedPrograms` 表中创建一个条目。此条目应在 `RecordedPrograms.COLUMN_RECORDING_DATA_URI` 列中包含录制的会话数据 URI，以及在最初调用 `onStartRecording()` 时系统提供的任何节目信息。
>
> 如需详细了解如何访问 `RecordedPrograms` 表，请参阅[管理录制的会话](https://developer.android.google.cn/training/tv/tif/content-recording#sessions)。

简单梳理`PVR`函数调用过程：

- `public TvInputService.RecordingSession onCreateRecordingSession (String inputId)` :

  返回`RecordingSession`的具体实现。

  如果此电视输入服务由于某种原因未能创建录制会话，则可能返回`null`。

- `TvInputService.RecordingSession`：提供电视输入录制会话具体实现的派生类。
- `TvContract.RecordedPrograms`：录制的电视节目表的列定义。

### 处理录制错误

如果录制期间发生错误，使录制的数据无法使用，应调用 `notifyError()` 来通知系统。同样，您也可以在创建录制会话后调用 `notifyError()`，以通知系统您的应用无法再录制会话。

如果在录制期间发生错误，但您希望提供部分录制内容供用户播放，应调用 `notifyRecordingStopped()` 以使系统能够使用部分会话。

### 管理录制的会话

系统在 `RecordedPrograms` 内容提供程序表中维护来自所有支持录制的频道应用的所有已录制会话的信息。此信息可通过 `RecordedPrograms` 内容录制 URI 访问。使用内容提供程序 API 读取、添加和删除此表中的条目。

如需详细了解如何使用内容提供程序数据，请参阅[内容提供程序基础知识](https://developer.android.google.cn/guide/topics/providers/content-provider-basics)。

### 最佳做法

TV 设备的存储空间可能有限，因此在分配存储空间以保存录制的会话时，请做出最佳判断。如果没有足够的空间存储录制的会话，请使用 `RecordingCallback.onError(RECORDING_ERROR_INSUFFICIENT_SPACE)`。

当用户发起录制时，您应尽快开始录制数据。为便于执行此操作，请在系统调用 `onCreateRecordingSession()` 回调时完成前期的所有耗时任务，如访问和分配存储空间。这样做可让您在 `onStartRecording()` 回调触发后立即开始录制。