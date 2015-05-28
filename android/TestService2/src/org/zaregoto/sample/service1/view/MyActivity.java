package org.zaregoto.sample.service1.view;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import org.zaregoto.sample.service.TestService2.R;
import org.zaregoto.sample.service1.service.IService;
import org.zaregoto.sample.service1.service.TestService;

public class MyActivity extends Activity {

    private final String TAG = "MyActivity";
    private IService service = null;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Button bindButton = (Button)findViewById(R.id.bindButton);
        bindButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent(getApplicationContext(), TestService.class);
                bindService(intent, connection, Context.BIND_AUTO_CREATE);

                Log.d(TAG, "bind service");

                return;
            }
        }
        );

        Button unbindButton = (Button)findViewById(R.id.unbindButton);
        unbindButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                unbindService(connection);

                Log.d(TAG, "unbind service");

                return;
            }
        }
        );

        CheckBox checkbox = (CheckBox)findViewById(R.id.foregroundFlag);
        checkbox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                Log.d(TAG, "toggle foreground");
            }
        });

    }

    @Override
    protected void onStart() {
        super.onStart();

        return;
    }

    @Override
    protected void onStop() {
        super.onStop();

        return;
    }


    private ServiceConnection connection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName name, IBinder binder) {
            service = IService.Stub.asInterface(binder);
            return;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            service = null;
            return;
        }
    };
}
