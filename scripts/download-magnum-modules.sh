# updates files in 'magnum_modules' directory
# run this every once in a while or when 'magnum_modules' is out of date
# WARNING: recursively deletes 'magnum_modules' directory, then replaces it
PROJECT_DIR=".."
MAGNUM_MODULES_DIR="${PROJECT_DIR}/magnum_modules"
TMP_MAGNUM_MODULES_DIR="./tmp_magnum_modules"

mkdir tmp_magnum_modules

./github-downloader.sh "https://github.com/mosra/magnum-extras/tree/master/modules"      && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules
./github-downloader.sh "https://github.com/mosra/magnum-integration/tree/master/modules" && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules
./github-downloader.sh "https://github.com/mosra/magnum-plugins/tree/master/modules"     && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules
./github-downloader.sh "https://github.com/mosra/magnum/tree/master/modules"             && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules
./github-downloader.sh "https://github.com/mosra/corrade/tree/master/modules"            && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules
./github-downloader.sh "https://github.com/mosra/toolchains/tree/master/modules"         && mv ./modules/*.cmake ${TMP_MAGNUM_MODULES_DIR}
rm -r ./modules

rm -r ${MAGNUM_MODULES_DIR}
mv ${TMP_MAGNUM_MODULES_DIR} ${MAGNUM_MODULES_DIR}
