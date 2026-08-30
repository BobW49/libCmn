#!/bin/bash -xv 

if cd misc ;then
	:
else
        echo "FATAL - CD failed!"
        exit 4
fi


if  genEnum --prefix=C_Expr --name=Class --files C_Expr_classes.txt ;then 
	cp C_Expr_Class_routines.c ../src/
	cp C_Expr_Class_tables.c   ../src/
	cp C_Expr_Class.h          ../src/
else
        echo "FATAL - genEnum - Sym_Classes failed!"
        exit 4
fi

if  genEnum --prefix=Sym --name=C_Prim --files sym_c_prim.txt ;then 
	cp Sym_C_Prim_routines.c ../src/
	cp Sym_C_Prim_tables.c   ../src/
	cp Sym_C_Prim.h          ../src/
else
        echo "FATAL - genEnum - Sym_Classes failed!"
        exit 4
fi

if  genEnum --prefix=Sym --name=Class --files sym_classes.txt ;then 
	cp Sym_Class_routines.c ../src/
	cp Sym_Class_tables.c   ../src/
	cp Sym_Class.h          ../src/
else
        echo "FATAL - genEnum - Sym_Classes failed!"
        exit 4
fi

if  genEnum --prefix=Sym --name=Phy_Prim --files sym_phy_prim.txt ;then 
	cp Sym_Phy_Prim_routines.c ../src/
	cp Sym_Phy_Prim_tables.c   ../src/
	cp Sym_Phy_Prim.h          ../src/
else
        echo "FATAL - genEnum - Sym_Phy_Prim failed!"
        exit 4
fi

if  genEnum --prefix=Tuple16 --name=Type --files Tuple16_Types.txt ;then 
	cp Tuple16_Type_routines.c ../src/
	cp Tuple16_Type_tables.c   ../src/
	cp Tuple16_Type.h          ../src/
else
        echo "FATAL - genEnum - Tuple_Type failed!"
        exit 4
fi

if  genEnum --prefix=Value --name=Type --files value_types.txt ;then 
	cp Value_Type_routines.c ../src/
	cp Value_Type_tables.c   ../src/
	cp Value_Type.h          ../src/
else
        echo "FATAL - genEnum - Value_Type failed!"
        exit 4
fi





