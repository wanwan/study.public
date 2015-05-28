package org.zaregoto.usoprogress;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ProgressBar;


public class MyActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.my, menu);
        return true;
    }

    @Override
    protected void onResume() {
        super.onResume();

        Thread th = new Thread(new Worker());
        th.start();

    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private int i = 0;

    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            ProgressBar p = (ProgressBar) findViewById(R.id.progressBar);
            if (null != p) {
                p.setProgress(i);
                i++;
            }

        }
    };

    class Worker implements Runnable {
        @Override
        public void run() {

            Message msg = new Message();
            try {
                Thread.sleep(1000);
                handler.sendMessage(msg);


                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

                Thread.sleep(1000);
                handler.sendMessage(msg);

            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

}
