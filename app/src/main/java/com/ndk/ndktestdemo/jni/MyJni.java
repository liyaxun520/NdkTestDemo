package com.ndk.ndktestdemo.jni;

public class MyJni {

    public native void giveArray(int[] array);

    public native int[] getArray(int arrLen);

    public native void createGlobalRef();

    public native String getGlobalRef();

    public native void deleteGlobalRef();


    public native void testException();

    public native void funOrraride();

    public native void nofirmParameterFunction();


}
