#!/bin/bash

# Number of expected command-line arguments
num_expected=2

if [ "$#" -ne "$num_expected" ]; then
  echo "Usage: ./addfakeweights.sh NTUPLE_LIST_FILE FULL_WEIGHT_FILE"
  #exit 1
fi

ntuple_list_file=$1
full_weight_file=$2

if [ ! -f "$ntuple_list_file" ]; then
  echo "Ntuple list file \"${ntuple_list_file}\" not found"
  #exit 1
fi

if [ ! -f "${full_weight_file}" ]; then
  echo "Full weight file \"${full_weight_file}\" not found"
  #exit 2
fi

# Loop over each line of the ntuple list file
while read line; do
  # Select lines that do not begin with a '#' character and contain at least
  # one non-whitespace character. These are assumed to be input files names
  if [[ ! $line = \#* ]] && [[ $line = *[^[:space:]]* ]]; then
    # Process the next input ntuple file
    input_file_name=$( echo $line | awk '{print $1}' )
    output_dir="$(dirname ${input_file_name})"
    input_file_basename="$(basename ${input_file_name})"
    output_file_name="${output_dir}/${input_file_basename%%.*}_fakeweights.${input_file_basename##*.}"
    echo "Processing ${input_file_name} --> ${output_file_name}"
    time ../build/FakeWeight ${full_weight_file} ${input_file_name} ${output_file_name}
  fi
done < "${ntuple_list_file}"