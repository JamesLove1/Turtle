
cd ${BASH_SOURCE[0]%/*}

echo -e "\n\e[4mMake Executables and Check Their Exsistance:\e[0m"
cd ../
make -s parse_s
make -s parse_v
make -s interp_s
make -s interp_v
make -s extension_s

if [ -f "parse_s" ];
then
    echo -e "FILE parse_s          \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE parse_s          \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -f "parse_v" ];
then
    echo -e "FILE parse_v          \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE parse_v          \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -f "interp_s" ];
then
    echo -e "FILE interp_s         \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE interp_s         \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -f "interp_v" ];
then
    echo -e "FILE interp_v         \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE interp_v         \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -f "extension_s" ];
then
    echo -e "FILE extension_s      \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE extension_s      \033[0;31mDOSE NOT EXISTS\033[0m"
fi
cd ./Testing

echo -e "\n\e[4mTest Parser Exit Codes:\e[0m"
mkdir ./temp
for TTL in ../TTLs/* ;
do 
    if [ "../TTLs/fail_parse_ok_interp.ttl" != "$TTL" ]; 
    then 
        ../parse_s "$TTL"
        error=$?
        if [ $error != 0 ]; then
            echo -e "\033[0;31mERROR\033[0m $TTL"
        fi
        echo -e "\033[0;32mPASSED\033[0m ${TTL}"
    fi
    if [ $TTL == "../TTLs/fail_parse_ok_interp.ttl" ]; 
    then 
        ../parse_s "$TTL" > ./temp/test_fail_parse_ok_interp 2>&1   
        error=$?
        if [ $error != 0 ]; then
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        fi
    fi
done

echo -e "\n\e[4mTest Parser for memory leaks using valgrind:\e[0m"
for TTL in ../TTLs/* ;
do 
    valgrind --leak-check=full --log-file=valgrind_output.txt ../parse_v $TTL > ./temp/testPaserMemLeaks 2>&1
    error=$?
    if [ "../TTLs/fail_parse_ok_interp.ttl" != "$TTL" ]; 
    then 
        if [ $error != 0 ]; 
        then
           echo -e "\033[0;31mERROR\033[0m $TTL"
        else
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        fi 
    fi
    if [ $TTL == "../TTLs/fail_parse_ok_interp.ttl" ]; 
    then
        if [ $error == 1 ];
        then
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        else
            echo -e "\033[0;31mERROR\033[0m $TTL"
        fi
    fi
done
 
echo -e "\n\e[4mTest Interpreter Exit Codes:\e[0m"
for TTL in ../TTLs/* ;
do 
    if [ "../TTLs/ok_parse_fail_interp.ttl" != "$TTL" ]; 
    then 
        ../interp_s "$TTL" TESTING > ./temp/testInterp 2>&1
        if [ $? != 0 ]; then
            echo -e "\033[0;31mERROR\033[0m $TTL"
        fi
        echo -e "\033[0;32mPASSED\033[0m ${TTL}"
    fi
    if [ $TTL == "../TTLs/ok_parse_fail_interp.ttl" ]; 
    then 
        ../interp_s "$TTL" TESTING > ./temp/ok_parse_fail_interp.ttl 2>&1    
        error=$?
        if [ $error == 1 ]; 
        then
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        else
            echo -e "\033[0;31mERROR\033[0m $TTL"
        fi
    fi
done

echo -e "\n\e[4mTest Interpreter for memory leaks using valgrind:\e[0m"
for TTL in ../TTLs/* ;
do 
    valgrind --leak-check=full --log-file=valgrind_output.txt ../interp_v "$TTL" TESTING > ./temp/testPaserMemLeaks 2>&1
    error=$?
    if [ "../TTLs/ok_parse_fail_interp.ttl" != "$TTL" ]; 
    then 
        if [ $error != 0 ]; 
        then
           echo -e "\033[0;31mERROR\033[0m $TTL"
           echo $error
        else
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        fi 
    fi
    if [ $TTL == "../TTLs/ok_parse_fail_interp.ttl" ]; 
    then
        if [ $error == 1 ];
        then
            echo -e "\033[0;32mPASSED\033[0m ${TTL}"
        else
            echo -e "\033[0;31mERROR\033[0m $TTL"
        fi
    fi
done
rm -rf temp
   
mkdir ./temp 
cd ./temp
echo -e "\n\e[4mTest Interpreter for .txt .ps .pdf outputs exsits:\e[0m"
if [ -d "../temp" ];
then
    echo -e "\033[0;32mEXISTS\033[0m    FILE turtle"
else
    echo -e "\033[0;31mDOSE NOT EXISTS\033[0m   FILE turtle"
fi
for TTL in ../../TTLs/* ;
do 
    if [ "../../TTLs/ok_parse_fail_interp.ttl" != "$TTL" ]; 
    then    
        removePath=${TTL##*/}
        removeExtension=${removePath%.*}
        comand="../../interp_s ${TTL} ./${removeExtension}.txt" 
        $comand
        comand="../../interp_s ${TTL} ./${removeExtension}.ps" 
        $comand
        isTXT=${removeExtension}.txt
        if [ -f "$isTXT" ];
        then
            echo -e "\033[0;32mEXISTS\033[0m    FILE ${removeExtension}.txt"
        else
            echo -e "\033[0;31mDOSE NOT EXISTS\033[0m      FILE ${removeExtension}.txt"
        fi
        isPS=${removeExtension}.ps
        if [ -f "$isPS" ];
        then
            echo -e "\033[0;32mEXISTS\033[0m    FILE ${removeExtension}.ps"
        else
            echo -e "\033[0;31mDOSE NOT EXISTS\033[0m     FILE ${removeExtension}.ps"
        fi
        isPDF=${removeExtension}.pdf
        if [ -f "$isPDF" ];
        then
            echo -e "\033[0;32mEXISTS\033[0m    FILE ${removeExtension}.pdf"
        else
            echo -e "\033[0;31mDOSE NOT EXISTS\033[0m      FILE ${removeExtension}.pdf"
        fi
    fi
done
cd ../
rm -rf temp


# 7. zip and check files are zipped  
cd ../
zip -r -q ./turtle ./Testing/ ./Parse ./Interp ./Extension ./Makefile ./neillsimplescreen.c neillsimplescreen.h ./TTLs
echo -e "\n\e[4mCheck Files Are Present:\e[0m"

unzip -q turtle.zip -d ./turtle

if [ -f "turtle.zip" ];
then
    echo -e "FILE turtle.zip          \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE turtle.zip          \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle" ];
then
    echo -e "FILE turtle              \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE turtle              \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle/Extension" ];
then
    echo -e "FILE Extension           \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE Extension           \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle/Interp" ];
then
    echo -e "FILE Interp              \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE Interp              \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle/Parse" ];
then
    echo -e "FILE Parse               \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE Parse               \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle/Testing" ];
then
    echo -e "FILE Testing             \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE Testing             \033[0;31mDOSE NOT EXISTS\033[0m"
fi

if [ -d "turtle/TTLs" ];
then
    echo -e "FILE TTLs                \033[0;32mEXISTS\033[0m"
else
    echo -e "FILE TTLs                \033[0;31mDOSE NOT EXISTS\033[0m"
fi
cd ./Testing


