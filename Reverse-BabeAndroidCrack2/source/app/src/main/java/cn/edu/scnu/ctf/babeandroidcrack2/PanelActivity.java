package cn.edu.scnu.ctf.babeandroidcrack2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class PanelActivity extends Activity {
    private String km = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_panel);

        Intent intent = getIntent();
        km = intent.getStringExtra("km");
    }

    public void onGetFlag(View v) {
        Toast.makeText(getApplicationContext(), getFlag(km), Toast.LENGTH_SHORT).show();
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String getFlag(String km);
}