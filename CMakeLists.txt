cmake_minimum_required(VERSION 3.13)

project(AnalyzeNue LANGUAGES CXX)

add_executable(AnalyzeNue src/AnalyseNue.cxx src/BDTTool.cxx src/CreateTrainingTree.cxx src/EventContainer.cxx src/Selection.cxx src/StackedHistTool.cxx src/Utility.cxx)

find_package(ROOT REQUIRED)
find_package(xgboost REQUIRED)

target_link_libraries(AnalyzeNue PUBLIC xgboost::xgboost ROOT::Core ROOT::Physics ROOT::Hist ROOT::Tree ROOT::Gpad)

