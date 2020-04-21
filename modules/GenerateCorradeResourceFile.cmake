function(generate_corrade_res_file _RES_DIR _RES_OUTFILE)
    get_filename_component(_RES_DIR ${_RES_DIR} ABSOLUTE)
    file(GLOB_RECURSE _RES_FILE_LIST
            LIST_DIRECTORIES false
            ${_RES_DIR}/*)

    get_filename_component(_RES_DIR_NAME ${_RES_DIR} NAME)

    file(WRITE ${_RES_OUTFILE}
            "group=${_RES_DIR_NAME}\n")

    foreach(_RES_FILE ${_RES_FILE_LIST})
        file(RELATIVE_PATH _RES_FILE_RELATIVE "${_RES_DIR}" "${_RES_FILE}")
        file(APPEND ${_RES_OUTFILE}
                "\n"
                "[file]\n"
                "filename=${_RES_FILE}\n"
                "alias=${_RES_FILE_RELATIVE}\n")
    endforeach(_RES_FILE)
endfunction(generate_corrade_res_file)