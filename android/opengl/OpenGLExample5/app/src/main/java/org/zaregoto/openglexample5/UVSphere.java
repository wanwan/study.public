package org.zaregoto.openglexample5;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

/**
 * Created by waka on 14/11/08.
 */
public class UVSphere {

    private int mStrips;
    private int mStripePointsNum;
    private ArrayList<FloatBuffer> mVertices;
    private ArrayList<FloatBuffer> mTextureCoords;

    private int[] mTextures = new int[1];

    private UVSphere() {
        mVertices = new ArrayList<FloatBuffer>();
        mTextureCoords = new ArrayList<FloatBuffer>();
    }

    public UVSphere(int radius, int divide) {
        this();

        mStrips = divide/2;
        mStripePointsNum = (divide+1)*2;
        makeVertices(radius, divide);
    }

    public void draw(GL10 gl10) {

        // bind the previously generated texture.
        gl10.glBindTexture(GL10.GL_TEXTURE_2D, this.mTextures[0]);

        // Point to our buffers.
        gl10.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        gl10.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);

        // Set the face rotation, clockwise in this case.
        gl10.glFrontFace(GL10.GL_CW);

        // Point to our vertex buffer.
        for (int i = 0; i < this.mStrips; i++) {
            gl10.glVertexPointer(3, GL10.GL_FLOAT, 0, this.mVertices.get(i));
            gl10.glTexCoordPointer(2, GL10.GL_FLOAT, 0, this.mTextureCoords.get(i));

            // Draw the vertices as triangle strip.
            gl10.glDrawArrays(GL10.GL_TRIANGLE_STRIP, 0, mStripePointsNum);
        }

        // Disable the client state before leaving.
        gl10.glDisableClientState(GL10.GL_VERTEX_ARRAY);
        gl10.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);

        return;
    }

    public void loadGLTexture(final GL10 gl, final Context context, final int texture) {
        final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), texture);

        // Generate one texture pointer, and bind it to the texture array.
        gl.glGenTextures(1, this.mTextures, 0);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, this.mTextures[0]);

        // Create nearest filtered texture.
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);

        // Use Android GLUtils to specify a two-dimensional texture image from our bitmap.
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);

        // Tidy up.
        bitmap.recycle();
    }


    private void makeVertices(int radius, int divide) {

        float theta1 = 0.0f, theta2 = 0.0f, theta3 = 0.0f;
        float cx = 0.0f, cy = 0.0f, cz = 0.0f;

        float ex = 0.0f, ey = 0.0f, ez = 0.0f;
        float px = 0.0f, py = 0.0f, pz = 0.0f;

        radius = Math.abs(radius);
        divide = Math.abs(divide);

        for(int i = 0; i < divide/2; ++i)
        {
            //theta1 = (float) (i * (Math.PI*2) / divide - Math.PI/2.0);
            //theta2 = (float) ((i + 1) * (Math.PI*2) / divide - Math.PI / 2.0);
            theta1 = (float) (Math.PI/2.0 -    i    * (Math.PI*2) / divide);
            theta2 = (float) (Math.PI/2.0 - (i + 1) * (Math.PI*2) / divide);


            float[] vertices = new float[divide*6+6];
            float[] normals =  new float[divide*6+6];
            float[] texCoords = new float[divide*4+4];

            for(int j = 0; j <= divide; ++j)
            {
                theta3 = (float) (j * (Math.PI*2) / divide);

                ex = (float) (Math.cos(theta2) * Math.cos(theta3));
                ey = (float)  Math.sin(theta2);
                ez = (float) (Math.cos(theta2) * Math.sin(theta3));
                px = cx + radius * ex;
                py = cy + radius * ey;
                pz = cz + radius * ez;

                vertices[(6*j)+(0%6)] = px;
                vertices[(6*j)+(1%6)] = py;
                vertices[(6*j)+(2%6)] = pz;

                normals[(6*j)+(0%6)] = ex;
                normals[(6*j)+(1%6)] = ey;
                normals[(6*j)+(2%6)] = ez;

                texCoords[(4*j)+(0%4)] = -(j/(float)divide);
                texCoords[(4*j)+(1%4)] = 2*(i+1)/(float)divide;


                ex = (float) (Math.cos(theta1) * Math.cos(theta3));
                ey = (float) Math.sin(theta1);
                ez = (float) (Math.cos(theta1) * Math.sin(theta3));
                px = cx + radius * ex;
                py = cy + radius * ey;
                pz = cz + radius * ez;

                vertices[(6*j)+(3%6)] = px;
                vertices[(6*j)+(4%6)] = py;
                vertices[(6*j)+(5%6)] = pz;

                normals[(6*j)+(3%6)] = ex;
                normals[(6*j)+(4%6)] = ey;
                normals[(6*j)+(5%6)] = ez;

                texCoords[(4*j)+(2%4)] = -(j/(float)divide);
                texCoords[(4*j)+(3%4)] = 2*i/(float)divide;
            }
//            glVertexPointer(3, GL_FLOAT, 0, vertices);
//            glNormalPointer(GL_FLOAT, 0, normals);
//            glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
//            glDrawArrays(GL_TRIANGLE_STRIP, 0, (p+1)*2);

            mVertices.add(makeFloatBufferFromArray(vertices));
            mTextureCoords.add(makeFloatBufferFromArray(texCoords));
        }
    }


    private FloatBuffer makeFloatBufferFromArray(float[] array) {

        FloatBuffer fb = ByteBuffer.allocateDirect(array.length*Float.SIZE).order(ByteOrder.nativeOrder()).asFloatBuffer();
        fb.put(array);
        fb.position(0);

        return fb;
    }


}
