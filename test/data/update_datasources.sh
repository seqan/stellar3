#!/bin/bash

echo -e "cmake_minimum_required (VERSION 3.16)\n" > datasources.cmake

echo -e "include (cmake/app_datasources.cmake)\n" >> datasources.cmake

for file in *.fasta
do
    [[ $file == *.sh ]] && continue # don't add script as datasource
    [[ -d $file ]] && continue      # skip folders
    echo -n "declare_datasource (FILE ${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/${file}
                URL_HASH SHA256=" >> datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> datasources.cmake
    echo ")" >> datasources.cmake
done

cd subset 

for file in *
do
    [[ $file == *.sh ]] && continue # don't add script as datasource
    [[ -d $file ]] && continue      # skip folders
    echo -n "declare_datasource (FILE subset_${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/subset/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done

cd ../segment

for file in *
do
    [[ $file == *.sh ]] && continue # don't add script as datasource
    [[ -d $file ]] && continue      # skip folders
    echo -n "declare_datasource (FILE segment_${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/segment/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done

cd ../er_edge_case

for file in *
do
    [[ $file == *.sh ]] && continue # don't add script as datasource
    [[ -d $file ]] && continue      # skip folders
    echo -n "declare_datasource (FILE er_edge_case_${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/er_edge_case/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done
