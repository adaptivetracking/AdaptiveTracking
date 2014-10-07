# AdaptiveTracking

This project contains a library and demo applications for adaptive real-time tracking in 2D image sequences. See the [project website](https://adaptivetracking.github.io/) for results and videos using the BoBoT dataset.


## Building the project


### Prerequisites

* [Boost](http://www.boost.org/) >= 1.48.0
* [OpenCV](http://opencv.org/) >= 2.4.3


### Linux

1. Clone the repository (e.g. `$ git clone https://github.com/adaptivetracking/AdaptiveTracking.git`), this will create a directory named `AdaptiveTracking`
2. If OpenCV or Boost cannot be found automatically by CMake (e.g. because they were not installed using the package manager), then create a file named `AdaptiveTracking/initial_cache.cmake` (copy `AdaptiveTracking/initial_cache.cmake.template`) and set the variables pointing to the installation directory
3. Create build directory next to `AdaptiveTracking`: `$ mkdir build`
4. Change to build directory: `$ cd build`
5. Build project
  * If using the initial cache: `$ cmake -C ../AdaptiveTracking/initial_cache.cmake -D CMAKE_BUILD_TYPE=Release ../AdaptiveTracking/`
  * If not using the initial cache: `$ cmake -D CMAKE_BUILD_TYPE=Release ../AdaptiveTracking/`
6. Compile the project: `$ make`


### Windows

1. Clone the repository (`$ git clone ...`), will create directory AdaptiveTracking
2. Create a file named `AdaptiveTracking/initial_cache.cmake` (copy `AdaptiveTracking/initial_cache.cmake.template`) and set the variables pointing to the installation directory of OpenCV (and maybe Boost)
3. Create build directory next to `AdaptiveTracking`: `$ mkdir build`
4. Change to build directory: `$ cd build`
5. Build project: `$ cmake -C ..\AdaptiveTracking\initial_cache.cmake -G "Visual Studio 12 Win64" ..\AdaptiveTracking`
6. Open the .sln file and compile the project using VisualStudio


## The libraries

* **libLogging:** Simple text logging to console or files
* **libImageIO:** Loading and storing image and annotation sequences
* **libImageProcessing:** Image filtering, pyramid construction, feature extraction
* **libClassification:** Classifiers with binary or probabilistic output, interfaces for classifiers that can be trained
* **libSvm:** Wrapper around [libSVM](http://www.csie.ntu.edu.tw/~cjlin/libsvm/) that complies with the interfaces of libClassification
* **libCondensation:** Particle filter based tracking


## The applications


### TrackingApp

This application shows the tracking on a single video. The tracking is initialized either via ground truth or manually, using a bounding box that is drawn with the mouse. Controls can influence the algorithm a little bit by changing the noise of the motion model, the particle count and other parameters. Other sliders control the visual output by drawing the particles or the optical flow. Optionally, an output video can be generated that contains the very same images that are shown on screen from the moment of the tracking initialization.

1. Change into the application directory: `cd build/TrackingApp`
2. Call the application: `./TrackingApp` with some options:
  1. Optional: Using a configuration other than `default.cfg`: `-c myconfig.cfg`
  2. Image sequence
    * Video file: `-v /path/to/video.avi`
    * Image directory: `-i /path/to/directory`
    * Camera: `-d 0` (device number - might be bigger in case of several camera devices)
  3. Optional: Giving a ground truth file containing bounding box information for each frame
    * BoBoT format: `-b /path/to/groundtruth.txt`
    * Simple format: `-s /path/to/groundtruth.txt`
  4. Optional: Output video
    1. Output video file: `-o /path/to/output-video.avi`
    2. Frame rate: `-f 25` (should match the FPS of the input data)
3. The video can be paused and resumed by pressing `p`
4. If no ground truth is given: Initialize the tracker by drawing a bounding box using the mouse
5. Exit the application by pressing `q`

Examples:

* `$ ./TrackingApp -d 0` (shows the videos stream of the webcam, tracking must be initialized manually)
* `$ ./TrackingApp -v /path/to/video.avi -b /path/to/groundtruth.txt -o /path/to/output-video.avi -f 25` (shows a video, tracking is initialized by ground truth, creates an output video with 25 FPS containing the frames with tracking output (bounding boxes))


### BenchmarkApp

This application runs test sequences on several algorithms, evaluating their performance. Two scores are computed: A hit ratio (the target is considered hit if the tracking bounding box and the ground truth bounding box have an overlap ratio of at least 50%) and the average overlap ratio. Detailled results (scores of each run and files containing the tracking output in the annotation format) can be found in the results directory.

1. Change into the application directory: `$ cd build/BenchmarkApp`
2. Adjust `tests.cfg` to include the annotated image sequences that should be used for the benchmark
3. Make copies of `algorithm.cfg` and adjust the values to compare several algorithm variations against each other
4. Call the application: `$ ./BenchmarkApp` with the following options in this order:
  1. Directory for storing the results: `/path/to/results`
  2. Configuration of the tests: `tests.cfg`
  3. Configurations of the algorithms: `algorithm1.cfg algorithm2.cfg ...`
5. Wait until the evaluation is finished, overall results can be seen on console, detailled results are in the result directory

Example:

* `$ ./BenchmarkApp bobot-results bobot.cfg BT.cfg OF.cfg LC.cfg OF-LC.cfg OF-LC-SW.cfg` (evaluates our tracking variations using the BoBoT dataset - see the [project website](https://adaptivetracking.github.io/) for the configuration files)


### PlayerApp

This application shows an image sequence, optionally drawing annotations on top. This can be used to create videos showing the ground truth and tracking outputs (if they are available). The colors can only be adjusted by changing the code.

1. Change into the application directory: `$ cd build/PlayerApp`
2. Call the application: `$ ./PlayerApp` with the following options in this order:
  1. Video file `/path/to/video.avi` or image directory `/path/to/directory`
  2. Optional: Annotation files containing bounding box information for each frame
    * BoBoT format: `-b /path/to/annotation1.txt /path/to/annotation2.txt ...`
    * Simple format: `-s /path/to/annotation1.txt /path/to/annotation2.txt ...`
  3. Optional: Output video
    1. Output video file: `-o /path/to/output-video.avi`
    2. Frame rate: `25` (should match the FPS of the input data)
    3. Optional: Codec: `DIVX` (four digit video codec (MJPG, DIVX, ...))
3. The video can be paused and resumed by pressing `p`
4. Wait until the replay is finished or exit by pressing `q`


Examples:

* `$ ./PlayerApp /path/to/video.avi` (shows a video)
* `$ ./PlayerApp /path/to/video.avi -b /path/to/ground-truth.txt /path/to/tracking-output.txt -o /path/to/output-video.avi 25 MJPG` (shows a video with ground truth annotations and tracking output and stores the video with both bounding boxes into a video file)

