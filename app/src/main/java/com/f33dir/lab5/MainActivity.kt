package com.f33dir.lab5

import android.net.Uri
import android.os.Bundle
import android.widget.Button
import android.widget.MediaController
import android.widget.VideoView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    lateinit var video:VideoView;
    lateinit var uri: Uri;
    lateinit var btnPlay : Button;
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        btnPlay = findViewById(R.id.playButton);
        btnPlay.setOnClickListener{play()}
        video = findViewById(R.id.videoView);
        uri = Uri.parse( "android.resource://" + getPackageName() + "/" + R.raw.videoplayback)
        video.setVideoURI(uri);
        val mediaController = MediaController(this)
        video.setMediaController(mediaController)
        mediaController.setMediaPlayer(video)

    }
    fun play() {
        video.start() //Начинает проигрование видео
    }

    fun pause() {
        video.pause() //Приостанавливает проигрование
    }

    fun stop() {
        video.stopPlayback() //Полностью останавлиевает видео
        video.resume() //Позволяет снова воспроизвести видео после остановки
    }

}