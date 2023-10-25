#!/bin/bash

while true
do
    echo -e "\n1. Insert record"
    echo "2. Display record"
    echo "3. Search record"
    echo "4. Delete record"
    echo "5. Modify record"
    echo "6. Exit"
    echo -n "Enter your choice: "
    read ch

    case $ch in
    1)
        echo -n "Enter employee no: "
        read eno
        echo -n "Enter employee name: "
        read ename
        echo -n "Enter employee phone number: "
        read eph
        echo -n "Enter employee city: "
        read ecity
        echo "$eno $ename $eph $ecity" >> emp1.txt
        ;;
    2)
        if [ -f "emp1.txt" ]; then
            cat emp1.txt
        else
            echo "No records found."
        fi
        ;;
    3)
        echo -n "Enter employee name to be searched: "
        read ename
        grep "$ename" emp1.txt
        ;;
    4)
        echo -n "Enter employee name to delete: "
        read ename
        grep -v "$ename" emp1.txt > temp.txt
        mv temp.txt emp1.txt
        ;;
    5)
        echo -n "Enter employee name to modify: "
        read ename
        echo -n "Enter new name: "
        read name
        sed -i "s/$ename/$name/g" emp1.txt
        ;;
    6)
        exit
        ;;
    *)
        echo "Invalid choice. Please select a valid option (1-6)."
        ;;
    esac
done

