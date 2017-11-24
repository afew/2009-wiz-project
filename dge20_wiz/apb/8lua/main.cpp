

#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>


#define MEDIA_DIR	"../../media/"

// Lua Instance
lua_State* g_pLuaSt;


// Lua Glue Function
static int Lua_Glue(lua_State *g_pLuaSt);



// Main Program
int main(int argc, char* argv[])
{
	int hr=0;

	// create lua instance
	g_pLuaSt = lua_open();


	// load Lua libraries
	luaopen_base(g_pLuaSt);
	luaopen_io(g_pLuaSt);
	luaopen_math(g_pLuaSt);
	luaopen_string(g_pLuaSt);
	luaopen_table(g_pLuaSt);



	// register lua glue function
	lua_register(g_pLuaSt, "LuaMyGlue", Lua_Glue);




	// do script file
	lua_dofile(g_pLuaSt, MEDIA_DIR"script.lua");



	// Get Lua API Function 
	lua_getglobal(g_pLuaSt, "Lua_MyApi");
	{
		// Call Lua API Function
		hr = lua_pcall(g_pLuaSt, 0, 0, 0);	// No argument to, No return from Lua API

		if(hr)
		{
			printf("lua api call error\n");
			lua_close(g_pLuaSt);
			return -1;
		}
	}


	lua_close(g_pLuaSt);
}






// Lua Glue Function

static int Lua_Glue(lua_State *g_pLuaSt)
{
	// Number of Arguemnt from Lua Script
	int n = lua_gettop(g_pLuaSt);

	printf("Argument Count: %d\n", n);



	int nCount = (int)lua_tonumber(g_pLuaSt, 1);

	printf("Count: %d\n", nCount);

	// No return
	return 0;
}



