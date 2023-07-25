cmake_minimum_required(VERSION 3.13)

find_package(ROOT REQUIRED)
find_package(xgboost REQUIRED)

project(AnalyzeNue LANGUAGES CXX)

add_executable(AnalyzeNue src/AnalyseNue.cxx src/BDTTool.cxx src/CreateTrainingTree.cxx src/EventContainer.cxx src/Selection.cxx src/SelectionDriver.cxx src/StackedHistTool.cxx src/Utility.cxx)
target_link_libraries(AnalyzeNue PUBLIC xgboost::xgboost ROOT::Core ROOT::Physics ROOT::Hist ROOT::Tree ROOT::Gpad)
target_include_directories(AnalyzeNue PRIVATE include)

ROOT_GENERATE_DICTIONARY(map_analyzenue_dict MODULE AnalyzeNue LINKDEF include/LinkDef.h)

project(ProcessNTuple LANGUAGES CXX)

add_executable(ProcessNTuple src/ProcessNTuple.cxx src/BDTTool.cxx src/EventContainer.cxx src/Selection.cxx src/Utility.cxx)
target_link_libraries(ProcessNTuple PUBLIC xgboost::xgboost ROOT::Core ROOT::Physics ROOT::Hist ROOT::Tree ROOT::Gpad)
target_include_directories(ProcessNTuple PRIVATE include)

ROOT_GENERATE_DICTIONARY(map_processntuple_dict MODULE ProcessNTuple LINKDEF include/LinkDef.h)