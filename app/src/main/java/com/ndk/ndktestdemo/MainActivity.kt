package com.ndk.ndktestdemo

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity;
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.widget.Toast
import com.ndk.ndktestdemo.jni.MyJni
import dou.utils.ToastUtil

import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    init {
        Log.d("TAG","加载库")
        System.loadLibrary("lison")
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)

        fab.setOnClickListener { view ->
            startActivity(Intent(this@MainActivity,SecondActivity::class.java))
        }

        var myJni = MyJni()
        var arrayOf = IntArray(10)
        //1, 10, 7, 4, 5, 8, 3, 2, 6, 9
        arrayOf[0] = 1
        arrayOf[1] = 10
        arrayOf[2] = 7
        arrayOf[3] = 4
        arrayOf[4] = 5
        arrayOf[5] = 8
        arrayOf[6] = 3
        arrayOf[7] = 2
        arrayOf[8] = 6
        arrayOf[9] = 9
        myJni.giveArray(arrayOf)
        arrayOf.forEach { Log.d("TAG", "排序后数据  $it") }

        var array = myJni.getArray(10)
        Log.d("TAG","===========================")
        array.forEach {
            Log.d("TAG","指定数组大小  $it")
        }

        myJni.funOrraride()

        myJni.nofirmParameterFunction()

    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when (item.itemId) {
            R.id.action_settings -> {
                Toast.makeText(this,"onOptionsItemSelected",Toast.LENGTH_SHORT).show()
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }


}
