/*
 * ConstantVelocityModel.hpp
 *
 *  Created on: 10.07.2012
 *      Author: poschmann
 */

#ifndef CONSTANTVELOCITYMODEL_HPP_
#define CONSTANTVELOCITYMODEL_HPP_

#include "condensation/TransitionModel.hpp"
#include "boost/random/normal_distribution.hpp"
#include "boost/random/mersenne_twister.hpp"
#include "boost/random/variate_generator.hpp"
#include <memory>

namespace condensation {

/**
 * Transition model that assumes a constant velocity (besides adding white noise to it).
 */
class ConstantVelocityModel : public TransitionModel {
public:

	/**
	 * Constructs a new simple transition model.
	 *
	 * @param[in] positionDeviation Standard deviation of the translation noise.
	 * @param[in] sizeDeviation Standard deviation of the scale change noise.
	 */
	explicit ConstantVelocityModel(double positionDeviation, double sizeDeviation);

	void init(const cv::Mat& image);

	void predict(std::vector<std::shared_ptr<Sample>>& samples, const cv::Mat& image, const std::shared_ptr<Sample> target);

	/**
	 * @return The standard deviation of the translation noise.
	 */
	double getPositionDeviation() const {
		return positionDeviation;
	}

	/**
	 * @param[in] deviation The new standard deviation of the translation noise.
	 */
	void setPositionDeviation(double deviation) {
		this->positionDeviation = deviation;
	}

	/**
	 * @return The standard deviation of the scale change noise.
	 */
	double getSizeDeviation() const {
		return sizeDeviation;
	}

	/**
	 * @param[in] deviation The new standard deviation of the scale change noise.
	 */
	void setSizeDeviation(double deviation) {
		this->sizeDeviation = deviation;
	}

private:

	double positionDeviation; ///< Standard deviation of the translation noise.
	double sizeDeviation;     ///< Standard deviation of the scale change noise.
	boost::variate_generator<boost::mt19937, boost::normal_distribution<>> generator; ///< Random number generator.
};

} /* namespace condensation */
#endif /* CONSTANTVELOCITYMODEL_HPP_ */
