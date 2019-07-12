package com.ndk.ndktestdemo;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import com.ndk.ndktestdemo.jni.SocketUtils;

public class SecondActivity extends AppCompatActivity {

    private SocketUtils socketUtils;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        socketUtils = new SocketUtils();
    }

    public void startServer(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int startServer = socketUtils.startServer();
            }
        }).start();

    }

    public void startClient(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int startClient = socketUtils.startClient();

            }
        }).start();

    }


}
