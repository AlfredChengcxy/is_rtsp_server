sed -i 's/fnc_log(FNC_LOG_VERBOSE,/xlog(LOG_INF,/g' $1
sed -i 's/fnc_log(FNC_LOG_DEBUG,/xlog(LOG_DBG,/g' $1
sed -i 's/fnc_log(FNC_LOG_INFO,/xlog(LOG_INF,/g' $1
sed -i 's/fnc_log(FNC_LOG_FATAL,/xlog(LOG_FAT,/g' $1
sed -i 's/fnc_log(FNC_LOG_WARN,/xlog(LOG_WAR,/g' $1
