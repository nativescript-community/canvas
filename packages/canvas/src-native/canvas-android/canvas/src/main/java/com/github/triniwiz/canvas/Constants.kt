package com.github.triniwiz.canvas

import android.opengl.GLES11Ext

/**
 * Created by triniwiz on 5/1/20
 */
object Constants {
	@JvmField
	var GL_RGBA16F_EXT = 0x881A
	@JvmField
	var GL_RGB16F_EXT = 0x881B
	@JvmField
	var GL_RG16F_EXT = 0x822F
	@JvmField
	var GL_R16F_EXT = 0x822D
	@JvmField
	var GL_R32F_EXT = 0x822E
	@JvmField
	var GL_RG32F_EXT = 0x8230
	@JvmField
	var GL_RGBA32F_EXT = 0x8814
	@JvmField
	var GL_RGB32F_EXT = 0x8815
	@JvmField
	var GL_MIN_EXT = 0x8007
	@JvmField
	var GL_MAX_EXT = 0x8008
	@JvmField
	var GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT = 0x8211
	@JvmField
	var GL_UNSIGNED_NORMALIZED_EXT = 0x8C17
	@JvmField
	var GL_SRGB_EXT = 0x8C40
	@JvmField
	var GL_SRGB_ALPHA_EXT = 0x8C42
	@JvmField
	var GL_SRGB8_ALPHA8_EXT = 0x8C43
	@JvmField
	var GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT = 0x8210
	@JvmField
	var GL_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FE
	@JvmField
	var GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FF
	@JvmField
	var GL_QUERY_COUNTER_BITS_EXT = 0x8864
	@JvmField
	var GL_CURRENT_QUERY_EXT = 0x8865
	@JvmField
	var GL_QUERY_RESULT_EXT = 0x8866
	@JvmField
	var GL_QUERY_RESULT_AVAILABLE_EXT = 0x8867
	@JvmField
	var GL_TIME_ELAPSED_EXT = 0x88BF
	@JvmField
	var GL_TIMESTAMP_EXT = 0x8E28
	@JvmField
	var GL_GPU_DISJOINT_EXT = 0x8FBB
	@JvmField
	var GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES = 0x8B8B
	@JvmField
	var GL_HALF_FLOAT_OES = 0x8D61
	@JvmField
	var GL_VERTEX_ARRAY_BINDING_OES = 0x85B5
	@JvmField
	var COMPRESSED_RGB_ATC_WEBGL = GLES11Ext.GL_ATC_RGB_AMD
	@JvmField
	var COMPRESSED_RGBA_ATC_EXPLICIT_ALPHA_WEBGL = GLES11Ext.GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
	@JvmField
	var COMPRESSED_RGBA_ATC_INTERPOLATED_ALPHA_WEBGL = GLES11Ext.GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
	@JvmField
	var GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG = 0x8C00
	@JvmField
	var GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG = 0x8C01
	@JvmField
	var GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG = 0x8C02
	@JvmField
	var GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG = 0x8C03
	@JvmField
	var GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0
	@JvmField
	var GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1
	@JvmField
	var GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2
	@JvmField
	var GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3
	@JvmField
	var GL_COMPRESSED_SRGB_S3TC_DXT1_EXT = 0x8C4C
	@JvmField
	var GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT = 0x8C4D
	@JvmField
	var GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT = 0x8C4E
	@JvmField
	var GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT = 0x8C4F
	@JvmField
	var GL_MAX_COLOR_ATTACHMENTS_EXT = 0x8CDF
	@JvmField
	var GL_MAX_DRAW_BUFFERS_EXT = 0x8824
	@JvmField
	var GL_DRAW_BUFFER0_EXT = 0x8825
	@JvmField
	var GL_DRAW_BUFFER1_EXT = 0x8826
	@JvmField
	var GL_DRAW_BUFFER2_EXT = 0x8827
	@JvmField
	var GL_DRAW_BUFFER3_EXT = 0x8828
	@JvmField
	var GL_DRAW_BUFFER4_EXT = 0x8829
	@JvmField
	var GL_DRAW_BUFFER5_EXT = 0x882A
	@JvmField
	var GL_DRAW_BUFFER6_EXT = 0x882B
	@JvmField
	var GL_DRAW_BUFFER7_EXT = 0x882C
	@JvmField
	var GL_DRAW_BUFFER8_EXT = 0x882D
	@JvmField
	var GL_DRAW_BUFFER9_EXT = 0x882E
	@JvmField
	var GL_DRAW_BUFFER10_EXT = 0x882F
	@JvmField
	var GL_DRAW_BUFFER11_EXT = 0x8830
	@JvmField
	var GL_DRAW_BUFFER12_EXT = 0x8831
	@JvmField
	var GL_DRAW_BUFFER13_EXT = 0x8832
	@JvmField
	var GL_DRAW_BUFFER14_EXT = 0x8833
	@JvmField
	var GL_DRAW_BUFFER15_EXT = 0x8834
	@JvmField
	var GL_COLOR_ATTACHMENT0_EXT = 0x8CE0
	@JvmField
	var GL_COLOR_ATTACHMENT1_EXT = 0x8CE1
	@JvmField
	var GL_COLOR_ATTACHMENT2_EXT = 0x8CE2
	@JvmField
	var GL_COLOR_ATTACHMENT3_EXT = 0x8CE3
	@JvmField
	var GL_COLOR_ATTACHMENT4_EXT = 0x8CE4
	@JvmField
	var GL_COLOR_ATTACHMENT5_EXT = 0x8CE5
	@JvmField
	var GL_COLOR_ATTACHMENT6_EXT = 0x8CE6
	@JvmField
	var GL_COLOR_ATTACHMENT7_EXT = 0x8CE7
	@JvmField
	var GL_COLOR_ATTACHMENT8_EXT = 0x8CE8
	@JvmField
	var GL_COLOR_ATTACHMENT9_EXT = 0x8CE9
	@JvmField
	var GL_COLOR_ATTACHMENT10_EXT = 0x8CEA
	@JvmField
	var GL_COLOR_ATTACHMENT11_EXT = 0x8CEB
	@JvmField
	var GL_COLOR_ATTACHMENT12_EXT = 0x8CEC
	@JvmField
	var GL_COLOR_ATTACHMENT13_EXT = 0x8CED
	@JvmField
	var GL_COLOR_ATTACHMENT14_EXT = 0x8CEE
	@JvmField
	var GL_COLOR_ATTACHMENT15_EXT = 0x8CEF
	var MAX_CLIENT_WAIT_TIMEOUT_WEBGL = 0x9247
}
