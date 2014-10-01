/*
 * VideoPlayer.hpp
 *
 *  Created on: 20.02.2014
 *      Author: poschmann
 */

#ifndef VIDEOPLAYER_HPP_
#define VIDEOPLAYER_HPP_

#include "imageio/ImageSource.hpp"
#include "imageio/ImageSink.hpp"
#include "imageio/AnnotationSource.hpp"
#include "opencv2/core/core.hpp"
#include <memory>
#include <vector>
#include <string>

/**
 * Video player that additionally shows annotations and may store the video with annotations into a new file.
 */
class VideoPlayer {
public:

	/**
	 * Constructs a new video player.
	 */
	VideoPlayer();

	/**
	 * Shows the images and annotations of the given sources and stores the images with annotations to an image sink.
	 *
	 * @param[in] imageSource The source of the images.
	 * @param[in] annotationSources The sources of the annotations (may be ommitted).
	 * @param[in] imageSink The sink for annotated images (may be ommitted).
	 */
	void play(std::shared_ptr<imageio::ImageSource> imageSource,
			std::vector<std::shared_ptr<imageio::AnnotationSource>> annotationSources = std::vector<std::shared_ptr<imageio::AnnotationSource>>(),
			std::shared_ptr<imageio::ImageSink> imageSink = std::shared_ptr<imageio::ImageSink>());

private:

	/**
	 * Callback that gets called whenever the slider of the stroke width was changed.
	 *
	 * @param[in] state The new value of the slider.
	 * @param[in] userdate The pointer to the video player.
	 */
	static void strokeWidthChanged(int state, void* userdata);

	/**
	 * Draws an annotation on top of an image.
	 * @param[in] image The image.
	 * @param[in] target The annotation.
	 * @param[in] color The color.
	 */
	void drawAnnotation(cv::Mat& image, const cv::Rect& target, const cv::Scalar& color);

	static const std::string videoWindowName; ///< The name of the window showing the video.
	static const std::string controlWindowName; ///< The name of the window showing the controls.

	bool paused; ///< Flag that indicates whether the video was paused.
	cv::Mat frame; ///< The current raw image from the source.
	cv::Mat image; ///< The currently shown image (with annotations drawn on top).
	std::vector<cv::Scalar> colors; ///< The colors used for the annotations.
	float strokeWidth; ///< The stroke width for drawing the annotations.
};

#endif /* VIDEOPLAYER_HPP_ */
