package cn.edu.scnu.ctf.babeandroidcrack2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import java.io.IOException;
import java.util.regex.Pattern;
import java.util.zip.CRC32;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends Activity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onLogin(View v) {
        EditText et = findViewById(R.id.activitymainEditText1);
        String km = et.getText().toString();
        if (km.length() != 8) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }
        String pattern = "^[0-9a-f]{8}$";
        if (!Pattern.matches(pattern, km)) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }

        CRC32 yz = new CRC32();
        yz.update("HSTCF#".getBytes());
        yz.update(km.getBytes());
        long yzm = yz.getValue();
        if (yzm != 242294092) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }

        yz.reset();
        yz.update("HSTCF#".getBytes());
        yz.update(km.getBytes());
        yz.update("#".getBytes());
        yz.update(String.valueOf(yzm).getBytes());
        long yzm2 = yz.getValue();
        System.out.println(yzm2);
        if (yzm2 != 3898757979L) {
            Toast.makeText(getApplicationContext(), "卡密不正确", Toast.LENGTH_SHORT).show();
            return;
        }

        Handler mHandler = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                Toast.makeText(getApplicationContext(), (String)msg.obj, Toast.LENGTH_SHORT).show();
            }
        };

        new Thread(() -> {
            try {
//                {
//                    Intent intent = new Intent(MainActivity.this, PanelActivity.class);
//                    intent.putExtra("km", km);
//                    startActivity(intent);
//                }

                String response = sendLogin("https://fake.doamin/login?km=" + km);
                if (response.equals("ok")) {
                    Intent intent = new Intent(MainActivity.this, PanelActivity.class);
                    intent.putExtra("km", km);
                    startActivity(intent);
                } else {
                    Message msg = new Message();
                    msg.obj = "卡密不正确";
                    mHandler.sendMessage(msg);
                }
            } catch (Exception e) {

                Message msg = new Message();
                msg.obj = "卡密不正确";
                mHandler.sendMessage(msg);
            }
        }).start();
    }

    OkHttpClient client = new OkHttpClient();
    String sendLogin(String url) throws IOException {
        Request request = new Request.Builder()
                .url(url)
                .build();

        try (Response response = client.newCall(request).execute()) {
            return response.body().string();
        }
    }

}