package org.zaregoto.openglexample5;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by waka on 14/11/08.
 */
public class GLRenderer implements GLSurfaceView.Renderer {

    /** Tilt the spheres a little. */
    private static final int AXIAL_TILT_DEGRESS = 30;

    /** Clear colour, alpha component. */
    private static final float CLEAR_RED = 0.0f;

    /** Clear colour, alpha component. */
    private static final float CLEAR_GREEN = 0.0f;

    /** Clear colour, alpha component. */
    private static final float CLEAR_BLUE = 0.0f;

    /** Clear colour, alpha component. */
    private static final float CLEAR_ALPHA = 0.5f;

    /** Perspective setup, field of view component. */
    private static final float FOVY = 45.0f;

    /** Perspective setup, near component. */
    private static final float Z_NEAR = 0.1f;

    /** Perspective setup, far component. */
    private static final float Z_FAR = 100.0f;

    /** Object distance on the screen. move it back a bit so we can see it! */
    private static final float OBJECT_DISTANCE = -15.0f;

    /** The earth's sphere. */
    private UVSphere mEarth;
    //private Sphere mEarth;

    /** The context. */
    private Context mContext;

    /** The rotation angle, just to give the screen some action. */
    private float mRotationAngle;


    private GLRenderer() {
    }

    public GLRenderer(Context context) {
        this.mContext = context;
        this.mEarth = new UVSphere(2, 40);
        //this.mEarth = new Sphere(3,2);
        this.mRotationAngle = 0.0f;
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

        this.mEarth.loadGLTexture(gl10, this.mContext, R.drawable.earth);
        gl10.glEnable(GL10.GL_TEXTURE_2D);
        gl10.glShadeModel(GL10.GL_SMOOTH);
        gl10.glClearColor(CLEAR_RED, CLEAR_GREEN, CLEAR_BLUE, CLEAR_ALPHA);
        gl10.glClearDepthf(1.0f);
        gl10.glEnable(GL10.GL_DEPTH_TEST);
        gl10.glDepthFunc(GL10.GL_LEQUAL);
        gl10.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_NICEST);

        return;
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {

        final float aspectRatio = (float) width / (float) (height == 0 ? 1 : height);

        gl10.glViewport(0, 0, width, height);
        gl10.glMatrixMode(GL10.GL_PROJECTION);
        gl10.glLoadIdentity();
        GLU.gluPerspective(gl10, FOVY, aspectRatio, Z_NEAR, Z_FAR);
        gl10.glMatrixMode(GL10.GL_MODELVIEW);
        gl10.glLoadIdentity();

        return;
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        gl10.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        gl10.glLoadIdentity();
        gl10.glTranslatef(0.0f, 0.0f, OBJECT_DISTANCE);
        gl10.glRotatef(AXIAL_TILT_DEGRESS, 1, 0, 0);
        gl10.glRotatef(this.mRotationAngle++, 0, 1, 0);
        this.mEarth.draw(gl10);
    }
}
