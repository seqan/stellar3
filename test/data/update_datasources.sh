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

for file in *.gff
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

for file in *.stdout
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
