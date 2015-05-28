package org.zaregoto.openglexample4;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;


public class MyActivity extends Activity {

    TestSurfaceView mSurface;
    GLRenderer mRenderer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my);

        mSurface = (TestSurfaceView) findViewById(R.id.surface);
        mSurface.setEGLContextClientVersion(2);

        mRenderer = new GLRenderer(this);
        mSurface.setRenderer(mRenderer);

        return;
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.my, menu);
        return true;
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


    @Override
    protected void onResume() {
        super.onResume();

        if (null != mSurface) {
            mSurface.onResume();
        }
        return;
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (null != mSurface) {
            mSurface.onPause();
        }
        return;
    }
}
