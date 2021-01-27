### AndroidManifest.xml

*receiver*:

```xml
        <receiver
            android:name="com.android.tv.tuner.TunerInputController$IntentReceiver"
            android:exported="false" >
            <intent-filter>
                <action android:name="android.intent.action.BOOT_COMPLETED" />
                <action android:name="android.hardware.usb.action.USB_DEVICE_ATTACHED" />
                <action android:name="android.hardware.usb.action.USB_DEVICE_DETACHED" />
                <action android:name="com.android.tv.action.APPLICATION_FIRST_LAUNCHED" />
                <action android:name="com.android.tv.action.NETWORK_TUNER_ATTACHED" />
                <action android:name="com.android.tv.action.NETWORK_TUNER_DETACHED" />
            </intent-filter>
        </receiver> <!-- DVR -->

<receiver android:name="com.android.tv.dvr.recorder.DvrStartRecordingReceiver" />
```

*service*:

```xml
        <service
            android:name="com.android.tv.dvr.recorder.DvrRecordingService"
            android:label="@string/dvr_service_name" />
```

### DvrRecordingService

packages/apps/TV/src/com/android/tv/dvr/recorder/DvrRecordingService.java

