# android.media.tv

## OverView

### Interfaces

| [TvContract.BaseTvColumns](https://developer.android.google.cn/reference/android/media/tv/TvContract.BaseTvColumns) | 电视频道/节目表的共同基础。                    |
| ------------------------------------------------------------ | ---------------------------------------------- |
| [TvView.OnUnhandledInputEventListener](https://developer.android.google.cn/reference/android/media/tv/TvView.OnUnhandledInputEventListener) | 收到未处理的输入事件时要调用的回调的接口定义。 |

### Classes

| [TvContentRating](https://developer.android.google.cn/reference/android/media/tv/TvContentRating) | 表示电视内容分级的类。                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [TvContract](https://developer.android.google.cn/reference/android/media/tv/TvContract) | 电视提供商与应用程序之间的合同。                             |
| [TvContract.Channels](https://developer.android.google.cn/reference/android/media/tv/TvContract.Channels) | 电视频道表的列定义。                                         |
| [TvContract.Channels.Logo](https://developer.android.google.cn/reference/android/media/tv/TvContract.Channels.Logo) | 单个电视频道的子目录，代表其主要logo。                       |
| [TvContract.PreviewPrograms](https://developer.android.google.cn/reference/android/media/tv/TvContract.PreviewPrograms) | 预览电视节目表的列定义。                                     |
| [TvContract.Programs](https://developer.android.google.cn/reference/android/media/tv/TvContract.Programs) | 电视节目表的列定义。                                         |
| [TvContract.Programs.Genres](https://developer.android.google.cn/reference/android/media/tv/TvContract.Programs.Genres) | 电视节目的规范。                                             |
| [TvContract.RecordedPrograms](https://developer.android.google.cn/reference/android/media/tv/TvContract.RecordedPrograms) | 录制的电视节目表的列定义。                                   |
| [TvContract.WatchNextPrograms](https://developer.android.google.cn/reference/android/media/tv/TvContract.WatchNextPrograms) | “观看下一个”电视节目表的列定义。                             |
| [TvInputInfo](https://developer.android.google.cn/reference/android/media/tv/TvInputInfo) | 该类用于指定电视输入的元信息。                               |
| [TvInputInfo.Builder](https://developer.android.google.cn/reference/android/media/tv/TvInputInfo.Builder) | 用于创建`TvInputInfo`对象的便利构建器。                      |
| [TvInputManager](https://developer.android.google.cn/reference/android/media/tv/TvInputManager) | 中央系统API到总体电视输入框架（TIF）架构，其仲裁应用程序和所选择的电视输入之间的交互。 |
| [TvInputManager.TvInputCallback](https://developer.android.google.cn/reference/android/media/tv/TvInputManager.TvInputCallback) | 回调用于监视电视输入的状态。                                 |
| [TvInputService](https://developer.android.google.cn/reference/android/media/tv/TvInputService) | TvInputService类代表电视输入或源，如HDMI或内置调谐器，可提供直通视频或广播电视节目。 |
| [TvInputService.HardwareSession](https://developer.android.google.cn/reference/android/media/tv/TvInputService.HardwareSession) | 电视输入会话的基类，代表连接到硬件电视输入的外部设备。       |
| [TvInputService.RecordingSession](https://developer.android.google.cn/reference/android/media/tv/TvInputService.RecordingSession) | 派生类的基类实现提供电视输入录音会话。                       |
| [TvInputService.Session](https://developer.android.google.cn/reference/android/media/tv/TvInputService.Session) | 用于实现提供电视输入会话的派生类的基类。                     |
| [TvRecordingClient](https://developer.android.google.cn/reference/android/media/tv/TvRecordingClient) | 公共接口对象，用于与特定的电视输入服务进行交互以进行电视节目录制。 |
| [TvRecordingClient.RecordingCallback](https://developer.android.google.cn/reference/android/media/tv/TvRecordingClient.RecordingCallback) | 回调用于在`TvInputService.RecordingSession`上接收各种状态更新 |
| [TvTrackInfo](https://developer.android.google.cn/reference/android/media/tv/TvTrackInfo) | 封装在TvInputService中播放的节目的格式。                     |
| [TvTrackInfo.Builder](https://developer.android.google.cn/reference/android/media/tv/TvTrackInfo.Builder) | 用于创建`TvTrackInfo`对象的构建器类。                        |
| [TvView](https://developer.android.google.cn/reference/android/media/tv/TvView) | 显示电视内容。                                               |
| [TvView.TimeShiftPositionCallback](https://developer.android.google.cn/reference/android/media/tv/TvView.TimeShiftPositionCallback) | 用于接收时移位置变化的回调。                                 |
| [TvView.TvInputCallback](https://developer.android.google.cn/reference/android/media/tv/TvView.TvInputCallback) | 回调用于在`TvView`上接收各种状态更新。                       |

## Interfaces

## Classes

### TvContentRating

表示电视内容分级的类。 当电视输入服务将节目的内容分级信息插入数据库时，此类可用于生成`TvContract.Programs＃COLUMN_CONTENT_RATING`的格式化字符串。 若要创建`TvContentRating`对象，请使用`TvContentRating.createRating`方法和有效的评分系统字符串常量。

 应用程序可以通过提供内容分级系统定义XML资源（请参见下面的示例）并声明一个在其清单中过滤`TvInputManager＃ACTION_QUERY_CONTENT_RATING_SYSTEMS`的广播接收器来定义其自己的内容分级系统。

### TvContract

电视提供商与应用程序之间的合同。 包含受支持的URI和列的定义。

TvContract定义了电视内容元数据（例如频道和节目信息）的基本数据库。 该信息存储在“频道”和“节目”表中。

频道表中的一行代表有关电视频道的信息。 数据格式随标准或服务提供商的不同而有很大的不同，因此此处的列主要由基本实体组成，无论标准如通道号和名称，用户通常都可以看到它们。

节目表中的一行代表一组描述电视节目的数据，例如节目标题和开始时间。

### TvContract.Channels

电视频道表的列定义。

### TvContract.Channels.Logo

单个电视频道的子目录，代表其主要徽标。

要访问此目录，请将`CONTENT_DIRECTORY`附加到原始通道URI。 生成的URI表示图像文件，应使用`ContentResolver.openAssetFileDescriptor`进行交互。

请注意，此子目录还支持以写模式将徽标作为资产文件打开。 呼叫者可以通过打开资产文件并将完整尺寸的照片内容写入其中来创建或替换与此频道关联的主要徽标。（确保徽标图像周围没有填充。）关闭文件时，将对图像进行解析，并在必要时缩小尺寸并存储。

### TvContract.PreviewPrograms

预览电视节目表的列定义。

### TvContract.Programs

电视节目表的列定义。

默认情况下，查询结果将按`Programs＃COLUMN_START_TIME_UTC_MILLIS`升序进行排序。

### TvContract.Programs.Genres

电视节目的规范流派。

### TvContract.RecordedPrograms

录制的电视节目表的列定义。

默认情况下，查询结果将按`COLUMN_START_TIME_UTC_MILLIS`升序排序。

### TvContract.WatchNextPrograms

观看下一个”电视节目表的列定义。

### TvInputInfo

此类用于指定电视输入的元信息。

### TvInputInfo.Builder

用于创建`TvInputInfo`对象的便捷构建器。

### TvInputManager

总体电视输入框架（TIF）架构的中央系统API，可仲裁应用程序与选定电视输入之间的交互。

电视输入框架（TIF）架构涉及三个主要方面：

- 此类表示的电视输入管理器是管理所有其他部分之间的交互的系统的中心点。它在这里表示为客户端`API`，它存在于每个应用程序上下文中，并与管理所有进程之间的交互的全局系统服务进行通信。

- 由`TvInputService`实现的电视输入代表电视的输入源，它可以是诸如`HDMI`之类的直通输入，也可以是提供广播电视节目的调谐器输入。系统根据每个应用程序的请求绑定到电视输入。关于实施电视输入。

- 应用程序与电视输入管理器对话，以列出电视输入并检查其状态。一旦应用程序找到要使用的输入，它将使用`TvView`或`TvRecordingClient`进行进一步的交互，例如观看和录制广播电视节目。


### TvInputManager.TvInputCallback

回调用于监视电视输入的状态。

### TvInputService

表示电视输入或源，例如提供直通视频或广播电视节目的HDMI或内置调谐器。

应用程序通常不会自己使用此服务，而是依靠TvView提供的标准交互。 那些实现电视输入服务的用户通常应从此类派生并基于`TvInputService.Session`提供自己的会话实现。 所有电视输入服务都必须要求客户端持有`Manifest.permission.BIND_TV_INPUT`才能与该服务进行交互； 如果清单中未指定此权限，则系统将拒绝绑定到该电视输入服务。

### TvInputService.HardwareSession

电视输入会话的基类，代表连接到硬件电视输入的外部设备。

此类用于输入，该输入为应用程序的外部机顶盒提供了通道。 电视输入在`TvInputService.onCreateSession（java.lang.String）`上返回此类的实现后，框架将为硬件电视输入（例如HDMI 1）创建一个单独的会话，并将应用程序的表面转发到该会话，以便 用户从该电视输入调谐到某个频道时，可以看到硬件电视输入的屏幕。 当应用程序请求`HardwareSession＃onTune`时，此类的实现预计将通过专有协议更改外部机顶盒的频道。

请注意，此类不适用于内置调谐器和`HDMI 1`等内部硬件的输入。

也可以看看：`TvInputService.onCreateSession（String）`

### TvInputService.RecordingSession

派生类的基类，实现以提供电视输入录制会话。

### TvInputService.Session

用于实现提供电视输入会话的派生类的基类。

### TvRecordingClient

公共接口对象，用于与特定的电视输入服务进行交互以进行电视节目录制。

### TvRecordingClient.RecordingCallback

用于在TvInputService.RecordingSession上接收各种状态更新的回调

### TvTrackInfo

封装在TvInputService中播放的曲目的格式。

### TvTrackInfo.Builder

用于创建TvTrackInfo对象的构建器类。

### **TvView**

显示电视内容。 TvView类为应用程序提供了一个高级界面，以显示来自实现`TvInputService`的各种电视来源的电视节目。 （请注意，可以通过调用`TvInputManager＃getTvInputList（）`获得系统上可用的电视输入列表。）一旦应用程序将特定电视频道的`URI`提供给`tune（String，Uri）`方法，它就会处理基础服务绑定（如果当前`TvView`已经绑定到服务，则取消绑定）并自动分配/取消分配所需的资源。 除了控制内容呈现方式的一些基本方法外，它还提供了一种将输入事件分派到连接的`TvInputService`的方法，以便为电视输入启用自定义按键操作。

### TvView.TimeShiftPositionCallback

用于接收时移位置变化的回调。

### TvView.TvInputCallback

回调用于在TvView上接收各种状态更新。













### TvInputManagerService：

治理着体系的种种输入，TV Input首要分为三品类型：hardware input:首要包括TV内建的种种输进端心，比方tuner、component, composite, hdmi。非hdmi