package org.zaregoto.openglexample4;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by waka on 14/11/08.
 */
public class GLRenderer implements TestSurfaceView.Renderer {

    private Context context;//アクティビティ
    private int      screenW; //画面幅
    private int      screenH; //画面高さ

    //バッファ

    private FloatBuffer vertexBuffer0;//頂点バッファ0
    private FloatBuffer vertexBuffer1;//頂点バッファ1
    private FloatBuffer uvBuffer;     //UVバッファ

    //テクスチャ
    private int textureId;//テクスチャID


    public GLRenderer(Context _context) {
        this.context = _context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

        //プログラムの生成
        ShaderUtil.makeProgram();

        //頂点配列の有効化
        GLES20.glEnableVertexAttribArray(ShaderUtil.positionHandle);
        GLES20.glEnableVertexAttribArray(ShaderUtil.uvHandle);

        //テクスチャの有効化
        GLES20.glEnable(GLES20.GL_TEXTURE_2D);

        //テクスチャの生成
        Bitmap bmp= BitmapFactory.decodeResource(
                context.getResources(), R.drawable.sample);
        textureId=makeTexture(bmp);

        //ブレンドの指定
        GLES20.glEnable(GLES20.GL_BLEND);
        GLES20.glBlendFunc(GLES20.GL_SRC_ALPHA,GLES20.GL_ONE_MINUS_SRC_ALPHA);

        //UVバッファの生成
        uvBuffer=makeUVBuffer();

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {

        GLES20.glViewport(0,0,width,height);
        screenW=width;
        screenH=height;

        //頂点バッファの生成
        vertexBuffer0=makeVertexBuffer(50,50,200,200);
        vertexBuffer1=makeVertexBuffer(50,300,300,300);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        //画面のクリア
        GLES20.glClearColor(1.0f,1.0f,1.0f,1.0f);
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        //テクスチャの指定
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,textureId);
        GLES20.glUniform1i(ShaderUtil.texHandle,0);

        //UVバッファの指定
        GLES20.glVertexAttribPointer(ShaderUtil.uvHandle,2,
                GLES20.GL_FLOAT,false,0,uvBuffer);

        //上の四角形の描画
        GLES20.glVertexAttribPointer(ShaderUtil.positionHandle,3,
                GLES20.GL_FLOAT,false,0,vertexBuffer0);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP,0,4);

        //下の四角形の描画
        GLES20.glVertexAttribPointer(ShaderUtil.positionHandle,3,
                GLES20.GL_FLOAT,false,0,vertexBuffer1);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP,0,4);

        return;
    }


    //UVバッファの生成
    private FloatBuffer makeUVBuffer() {
        float[] uvs={
                0.0f,0.0f,//左上
                0.0f,1.0f,//左下
                1.0f,0.0f,//右上
                1.0f,1.0f,//右下
        };
        return makeFloatBuffer(uvs);
    }

    //テクスチャの生成
    private int makeTexture(Bitmap bmp) {
        //テクスチャメモリの確保
        int[] textureIds=new int[1];
        GLES20.glGenTextures(1,textureIds,0);

        //テクスチャへのビットマップ指定
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,textureIds[0]);
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bmp, 0);

        //テクスチャフィルタの指定
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                GLES20.GL_TEXTURE_MIN_FILTER,GLES20.GL_NEAREST);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                GLES20.GL_TEXTURE_MAG_FILTER,GLES20.GL_NEAREST);
        return textureIds[0];
    }

    //頂点バッファの生成
    private FloatBuffer makeVertexBuffer(int x,int y,int w,int h) {
        //ウィンドウ座標を正規化デバイス座標に変換
        float left  =((float)x/(float)screenW)*2.0f-1.0f;
        float top   =((float)y/(float)screenH)*2.0f-1.0f;
        float right =((float)(x+w)/(float)screenW)*2.0f-1.0f;
        float bottom=((float)(y+h)/(float)screenH)*2.0f-1.0f;
        top   =-top;
        bottom=-bottom;

        //頂点バッファの生成
        float[] vertexs={
                left, top,   0.0f,//頂点0
                left, bottom,0.0f,//頂点1
                right,top,   0.0f,//頂点2
                right,bottom,0.0f,//頂点3
        };
        return makeFloatBuffer(vertexs);
    }

    //float配列をFloatBufferに変換
    private FloatBuffer makeFloatBuffer(float[] array) {
        FloatBuffer fb= ByteBuffer.allocateDirect(array.length * 4).order(
                ByteOrder.nativeOrder()).asFloatBuffer();
        fb.put(array).position(0);
        return fb;
    }
}
