#!/bin/bash

PKG=BsReactNative

OUTPUT=./build/odoc-html
LIB=../bs-react-native/lib/bs/src
PAGES=./pages
PUBLIC=./public
ODOC=$(which odoc)
if [[ $? != 0 ]] ; then
  echo "Missing odoc, please look at the CONTRIBUTING.md guide"
  exit 1
fi

mkdir -p ${OUTPUT}

# Gather the sources to compile .odoc files
CMT_FILES=$(find ${LIB} -name "*.cmti")
MLD_FILES=$(find ${PAGES} -name "*.mld")

echo "<< Compiling module docs..."
for file in ${CMT_FILES}; do
  ${ODOC} compile \
    -I ${LIB} \
    --pkg=${PKG} \
    --resolve-fwd-refs \
    ${file} \
  || exit 1
done

echo "<< Compiling page docs..."
for file in ${MLD_FILES}; do
  odoc_file=$( echo $(basename ${file}) | sed "s/mld/odoc/")
  ${ODOC} compile \
    -I ${LIB} \
    --pkg=${PKG} \
    --resolve-fwd-refs \
    -o ${LIB}/${odoc_file} \
    ${file} \
  || exit 1
done

# Now we can look for the compiled .odoc files
ODOC_FILES=$(find ${LIB} -name "*.odoc")

echo "<< Generating HTML..."
for file in ${ODOC_FILES}; do
  ${ODOC} html \
    -I ${LIB} \
    -o ${OUTPUT} \
    --syntax=re \
    --semantic-uris \
    ${file} \
  || exit 1
done
