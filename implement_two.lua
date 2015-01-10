--LUA

function test_func_runtime_changes(num)
	local result = test_runtime_changes(num)
	result = result + 200
	return result
end
