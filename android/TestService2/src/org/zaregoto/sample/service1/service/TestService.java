package org.zaregoto.sample.service1.service;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import org.zaregoto.sample.service.TestService2.R;
import org.zaregoto.sample.service1.view.MyActivity;

/**
 * Created with IntelliJ IDEA.
 * User: waka
 * Date: 2013/04/09
 * Time: 5:04
 * To change this template use File | Settings | File Templates.
 */
public class TestService extends Service {

    private static final String TAG = "TestService";
    private boolean foreground = true;

    @Override
    public IBinder onBind(Intent intent) {

        Log.d(TAG, "TestService onBind");

        return mBinder.get();
    }

    @Override
    public void onCreate() {
        super.onCreate();

        Log.d(TAG, "TestService onCreate");
        return;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        Log.d(TAG, "TestService onDestroy");
        return;
    }

    private final ThreadLocal<IService.Stub> mBinder = new ThreadLocal<IService.Stub>() {
        @Override
        protected IService.Stub initialValue() {
            return new IService.Stub() {

                Notification notification = new Notification.Builder(TestService.this)
                        .setContentTitle(getString(R.string.notification))
                        .setContentText("")
                        .setSmallIcon(R.drawable.ic_silmeewave).build();

                Intent notificationIntent = new Intent(TestService.this, MyActivity.class);
                //PendingIntenet pendingIntent = PendingIntent.getActivity(TestService.this, 0, notificationIntent, 0);

                @Override
                public boolean isForeground() throws RemoteException {
                    return foreground;
                }

                @Override
                public void setForeground(boolean foreground) throws RemoteException {

                    if (foreground) {
                        TestService.this.startForeground(0, notification);
                    } else {

                    }

                    TestService.this.foreground = foreground;

                    return;

                }
            };
        }
    };
}


