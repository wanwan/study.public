package com.example.NotifierSample;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.text.SimpleDateFormat;

public class MyActivity extends Activity implements View.OnClickListener {
    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Button notifyBtn = (Button) findViewById(R.id.notifybtn);
        notifyBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {

        Notification n = new Notification();
        n.icon = R.drawable.ic_launcher;
        n.tickerText = "ティッカーテキスト";
        n.number = 2;
        try{
            SimpleDateFormat date = new SimpleDateFormat("yy/mm/dd HH:mm");
            n.when = date.parse("2010/5/20").getTime();
        }catch(Exception e){
            n.when = System.currentTimeMillis();
        }

        Intent i = new Intent(getApplicationContext(), MyActivity.class);
        PendingIntent pend = PendingIntent.getActivity(this, 0, i, 0);
        n.setLatestEventInfo(getApplicationContext(), "タイトル", "テキスト", pend);


        NotificationManager mManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        mManager.notify(1,n);

        return;
    }
}
