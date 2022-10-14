package org.nativescript.canvas

import android.content.Context
import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.drawable.BitmapDrawable
import android.util.Log
import java.io.ByteArrayOutputStream
import java.net.URL
import java.nio.ByteBuffer
import java.util.concurrent.CountDownLatch
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit

/**
 * Created by triniwiz on 5/4/20
 */
class NSCImageAsset {

	interface Callback {
		fun onComplete(done: Boolean)
	}

	fun saveAsync(asset: Long ,path: String, format: Int, callback: Callback) {
		executorService.execute {
			val done = nativeSave(asset, path, format);
			callback.onComplete(done)
		}
	}

	fun loadImageFromResource(asset: Long ,id: Int, context: Context): Boolean {
		var hasError: Boolean
		try {
			val drawable =
				if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
					context.resources.getDrawable(id, null)
				} else {
					context.resources.getDrawable(id)
				}

			return loadImageFromBitmap(
				asset,
				(drawable as? BitmapDrawable)?.bitmap ?: run {
					val bitmap = Bitmap.createBitmap(
						drawable.intrinsicWidth,
						drawable.intrinsicHeight,
						Bitmap.Config.ARGB_8888
					)
					val canvas = Canvas(bitmap)
					drawable.draw(canvas)
					bitmap
				}
			)
		} catch (e: Exception) {
			hasError = true
			nativeSetError(asset, e.toString())
		}

		return !hasError
	}

	fun loadImageFromUrlAsync(asset: Long, url: String, callback: Callback) {
		executorService.execute {
			val done = nativeLoadFromUrl(asset, url)
			callback.onComplete(done)
		}
	}

	fun loadImageFromPathAsync(asset: Long, path: String, callback: Callback) {
		executorService.execute {
			val done = nativeLoadFromPath(asset, path)
			callback.onComplete(done)
		}
	}

	fun loadImageFromBytesAsync(asset: Long, buffer: ByteArray, callback: Callback) {
		executorService.execute {
			val done = nativeLoadFromBytes(asset, buffer)
			callback.onComplete(done)
		}
	}

	fun loadImageFromBufferAsync(asset: Long, buffer: ByteBuffer, callback: Callback) {
		executorService.execute {
			val done = nativeLoadFromBuffer(asset, buffer)
			callback.onComplete(done)
		}
	}

	fun loadImageFromBitmap(asset: Long, bitmap: Bitmap): Boolean {
		return nativeLoadFromBitmap(asset, bitmap)
	}

	fun loadImageFromBitmapAsync(asset: Long,bitmap: Bitmap, callback: Callback) {
		executorService.execute {
			val done = nativeLoadFromBitmap(asset, bitmap)
			callback.onComplete(done)
		}
	}

	companion object {

		init {
			TNSCanvas.loadLib()
		}

		@JvmStatic
		private external fun nativeSave(asset: Long, path: String, format: Int): Boolean

		@JvmStatic
		private external fun nativeLoadFromPath(asset: Long, path: String): Boolean

		@JvmStatic
		private external fun nativeLoadFromBytes(asset: Long, buffer: ByteArray): Boolean

		@JvmStatic
		private external fun nativeLoadFromBuffer(asset: Long, buffer: ByteBuffer): Boolean

		@JvmStatic
		private external fun nativeLoadFromUrl(asset: Long, path: String): Boolean

		@JvmStatic
		private external fun nativeLoadFromBitmap(asset: Long, bitmap: Bitmap): Boolean

		@JvmStatic
		private external fun nativeSetError(asset: Long, error: String)

		private val executorService = Executors.newCachedThreadPool()
	}

}
