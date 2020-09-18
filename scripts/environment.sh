################################################################################
# environment.sh
#
# Description: Set environment variables for running scripts.
# Usage:       source environment.sh
################################################################################

#!/usr/bin/env bash

# Export paths to environment (do not include trailing forward slash)
export ASTRO_ACCELERATE_REPOSITORY_PATH=/home/guest/Rushikesh/FRB_pipeline-1.7.10.GMRT300-500/
export ASTRO_ACCELERATE_EXECUTABLE_PATH=${ASTRO_ACCELERATE_REPOSITORY_PATH}
export ASTRO_ACCELERATE_SCRIPTS_PATH=${ASTRO_ACCELERATE_REPOSITORY_PATH}/scripts
export ASTRO_ACCELERATE_SCRIPTS_UNIT_TESTS_OUTPUT_PATH=${ASTRO_ACCELERATE_REPOSITORY_PATH}
export ASTRO_ACCELERATE_PROFILING_OUTPUT_PATH=${ASTRO_ACCELERATE_REPOSITORY_PATH}/build
export ASTRO_ACCELERATE_EXAMPLE_EXECUTABLE_PATH=${ASTRO_ACCELERATE_REPOSITORY_PATH}/examples/src
