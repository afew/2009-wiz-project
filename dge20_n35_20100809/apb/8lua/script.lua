
-- lua�� �ּ��� "--"�Դϴ�.

count =0


function Lua_MyApi()

	while true do
		if count == 100 then
			break
		end

		-- 1 �� ����
		count = count + 1

		-- call lua glue function
		LuaMyGlue(count)
		
	end

	return 0

end

