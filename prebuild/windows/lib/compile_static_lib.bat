cd src
cl /O2 /W3 /c /DLUA_BUILD_AS_DLL l*.c
:: we don't need lua.obj luac.obj to link lib53.lib
del lua.obj luac.obj
rem link /DLL /out:lua53.dll l*.obj
link /LIB /out:lua53.lib l*.obj

del l*.obj
cd ..