//
//  Constants.hpp
//  Social Matrix Simulation
//
//  Created by Aldric Labarthe on 14/11/2023.
//

#include "CMakeConsts.h"

#define SMS_VERSION "0.6 30/07/24"

#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <random>
#include <cassert>
#include <ctime>
#include <chrono>
#include <memory>
#include <thread>
#include <random>
#include <algorithm>
#include <filesystem>
#include <deque>

#ifndef GRAPH_SIZE
    #define GRAPH_SIZE (20)
#endif

#ifndef MAX_THREADS_USAGE
    #define MAX_THREADS_USAGE (85)
#endif

#define MODE_ECO_LOG 0
#define MODE_FOLDER_LOG 1

#define DEPRECIATION_RATE (0.001)
#define MIN_LINK_WEIGHT (0.005)
#define MAX_LINK_CHANGE (0.15)

#ifndef Constants_h
#define Constants_h

//#include "SocialMatrix.hpp"
//#include "Individual.hpp"

#endif /* Constants_h */
