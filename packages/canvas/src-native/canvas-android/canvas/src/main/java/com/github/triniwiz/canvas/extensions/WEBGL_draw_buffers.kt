package com.github.triniwiz.canvas.extensions

import android.opengl.GLES30
import android.os.Build
import androidx.annotation.RequiresApi
import com.github.triniwiz.canvas.Constants

/**
 * Created by triniwiz on 5/1/20
 */
@RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
class WEBGL_draw_buffers {
	var COLOR_ATTACHMENT0_WEBGL = Constants.GL_COLOR_ATTACHMENT0_EXT
	var COLOR_ATTACHMENT1_WEBGL = Constants.GL_COLOR_ATTACHMENT1_EXT
	var COLOR_ATTACHMENT2_WEBGL = Constants.GL_COLOR_ATTACHMENT2_EXT
	var COLOR_ATTACHMENT3_WEBGL = Constants.GL_COLOR_ATTACHMENT3_EXT
	var COLOR_ATTACHMENT4_WEBGL = Constants.GL_COLOR_ATTACHMENT4_EXT
	var COLOR_ATTACHMENT5_WEBGL = Constants.GL_COLOR_ATTACHMENT5_EXT
	var COLOR_ATTACHMENT6_WEBGL = Constants.GL_COLOR_ATTACHMENT6_EXT
	var COLOR_ATTACHMENT7_WEBGL = Constants.GL_COLOR_ATTACHMENT7_EXT
	var COLOR_ATTACHMENT8_WEBGL = Constants.GL_COLOR_ATTACHMENT8_EXT
	var COLOR_ATTACHMENT9_WEBGL = Constants.GL_COLOR_ATTACHMENT9_EXT
	var COLOR_ATTACHMENT10_WEBGL = Constants.GL_COLOR_ATTACHMENT10_EXT
	var COLOR_ATTACHMENT11_WEBGL = Constants.GL_COLOR_ATTACHMENT11_EXT
	var COLOR_ATTACHMENT12_WEBGL = Constants.GL_COLOR_ATTACHMENT12_EXT
	var COLOR_ATTACHMENT13_WEBGL = Constants.GL_COLOR_ATTACHMENT13_EXT
	var COLOR_ATTACHMENT14_WEBGL = Constants.GL_COLOR_ATTACHMENT14_EXT
	var COLOR_ATTACHMENT15_WEBGL = Constants.GL_COLOR_ATTACHMENT15_EXT
	var DRAW_BUFFER0_WEBGL = Constants.GL_DRAW_BUFFER0_EXT
	var DRAW_BUFFER1_WEBGL = Constants.GL_DRAW_BUFFER1_EXT
	var DRAW_BUFFER2_WEBGL = Constants.GL_DRAW_BUFFER2_EXT
	var DRAW_BUFFER3_WEBGL = Constants.GL_DRAW_BUFFER3_EXT
	var DRAW_BUFFER4_WEBGL = Constants.GL_DRAW_BUFFER4_EXT
	var DRAW_BUFFER5_WEBGL = Constants.GL_DRAW_BUFFER5_EXT
	var DRAW_BUFFER6_WEBGL = Constants.GL_DRAW_BUFFER6_EXT
	var DRAW_BUFFER7_WEBGL = Constants.GL_DRAW_BUFFER7_EXT
	var DRAW_BUFFER8_WEBGL = Constants.GL_DRAW_BUFFER8_EXT
	var DRAW_BUFFER9_WEBGL = Constants.GL_DRAW_BUFFER9_EXT
	var DRAW_BUFFER10_WEBGL = Constants.GL_DRAW_BUFFER10_EXT
	var DRAW_BUFFER11_WEBGL = Constants.GL_DRAW_BUFFER11_EXT
	var DRAW_BUFFER12_WEBGL = Constants.GL_DRAW_BUFFER12_EXT
	var DRAW_BUFFER13_WEBGL = Constants.GL_DRAW_BUFFER13_EXT
	var DRAW_BUFFER14_WEBGL = Constants.GL_DRAW_BUFFER14_EXT
	var DRAW_BUFFER15_WEBGL = Constants.GL_DRAW_BUFFER15_EXT
	var MAX_COLOR_ATTACHMENTS_WEBGL = Constants.GL_MAX_COLOR_ATTACHMENTS_EXT
	var MAX_DRAW_BUFFERS_WEBGL = Constants.GL_MAX_DRAW_BUFFERS_EXT
	fun drawBuffersWEBGL(buffers: IntArray) {
		GLES30.glDrawBuffers(buffers.size, buffers, 0)
	}
}