
-- 필수기본 변수를 불러온다.
-----------------------------------------------------------------------
function Set_varible()

	CurTime = 0; 	STimer = 0		--프레임타임 기준변수
	mposx = 0; mposy = 0			--마우스X,y좌표
	mLb = 0; mRb= 0; mMb = 0		--마우스 버튼

	Key = {}				--키보드 입력
	for i = 1,256 do		Key[i] = 0	end

	gCurpage = 0			--현재 페이지 (0; 타이틀, 1;스테이지선택, 2;게임플레이, 3;결과정산, 4;엔딩/종료)
	gNextPage = 0			--다음 페이지(페이지전환중 사용)
	gBasicfct = 0			-- +1일반 영구 카운터(프레임기준 10)

	shim = 0		--디버그/체크용 변수

	return 0
end

-- 기본적인 세팅( 1.타이머, 2. 마우스, 3.키보드)
-------------------------------------------------------------------------------
function Set_input()

	--1. 타이머
	CurTime = Lsys.GetTickCount()						--ms(밀리세컨드)

	--2. 마우스
	mposx, mposy, mposz = Lin.MousePos()		-- 마우스 포지션
	mLb, mRb, mMb = Lin.MouseEvnt()				-- 마우스 이벤트(0:입력없음,1:Down,3:Pressed)

	--3. 키보드
	for i=1,256 do	 --9(TAB), 13(엔터), 27(ESC), 32(SPACE), 33(PAGEUP), 38(CUR-UP), 49~(1), 65~(A), 112~(F1)
		Key[i] = Lin.KeyboardOne(i)					-- 키보드 이벤트(0:입력없음,1:Down,3:Pressed)
	end

	return 0
end

--[충돌1] 점(point)과 영역(rect)의 체크
---------------------------------------------------------------------------
function PointInRect(_px, _py, _rx, _ry, _rw, _rh)

	if (_px >= _rx) and (_px <= _rx + _rw) and
		(_py >= _ry) and (_py <= _ry + _rh)
		then
			
		return 1
	end

	return 0
end

--[충돌2] 점(point)과 영역(circle)의 충돌체크
---------------------------------------------------------------------------
function PointInCircle(_px, _py, _cx, _cy, _cr)
	
	if ((_cr^2) >= ((_cx - _px)^2)+((_cy - _py)^2) ) 
		then

		return 1
	end

	return 0
end

--[충돌3] 영역(rect1)과 영역(rect2)간의 충돌 체크 
---------------------------------------------------------------------------
function RectInRect(_r1px, _r1py, _r1w, _r1h, _r2px, _r2py, _r2w, _r2h)

	--r1의 좌상단x가 r2우하단x보다 작다	_r1px <= _r2px+_r2w
	--r1의 좌상단y가 r2우하단y보다 작다 _r1py <= _r2py+_r2h
	--r1의 우하단x가 r2좌상단x보다 크다 _r1px+_r1w >= _r2px
	--r1의 우하단y가 r2좌상단y보다 크다 _r1py+_r1h >= _r2py

	if (_r1px <= _r2px+_r2w) and (_r1py <= _r2py+_r2h) and
		(_r1px+_r1w >= _r2px) and (_r1py+_r1h >= _r2py) then			
		return 1
	end

	return 0
end

--[충돌4] 원-원 간의 충돌 체크 (c1의 좌상단좌표, c1텍스처 width, c2의 좌상단좌표, c2텍스처 width)
---------------------------------------------------------------------------
function CircleInCircle(c1posx, c1posy, c1width, c2posx, c2posy, c2width)

	--c1, c2의 반지름연산
	local c1r, c2r
	c1r = c1width/2
	c2r = c2width/2

	--c1, c2의 중심좌표연산
	local c1x, c1y, c2x, c2y
	c1x = c1posx + c1r ; 	c1y = c1posy + c1r
	c2x = c2posx + c2r ; 	c2y = c2posy + c2r

	--c1, c2의 중심점 사이의 거리연산
	local xx = ((c2x - c1x)^2) + ((c2y - c1y)^2)
	xx = math.sqrt(xx)
	
	--중심간거리(xx)가 c1, c2 반지름의 합보다 작으면 두원은 겹쳐있음(return 1)
	if ( xx <= (c1r+c2r) ) then
		return 1
	end

	return 0
end


--버튼을 그리는 약식함수(2종버튼- 일반/클릭)
---------------------------------------------------------------------
function byButtonDraw(txid, bposx, bposy, bwidth, bheight)

	if (mposx >= bposx) and (mposx <= bposx + bwidth) and
		(mposy >= bposy) and (mposy <= bposy + bheight)		then
			
		--버튼 롤오버 or 클릭
		Ltex.Draw(txid, 0, Ltex.Height(txid)/2, Ltex.Width(txid), Ltex.Height(txid), bposx, bposy)

		if mLb == 1 then Lsmd.Play(PlaySound[1], 0) end

		if (mLb == 2) then		return 2
		else					return 1
		end		

	else
		--버튼 일반상태
		Ltex.Draw(txid, 0, 0, Ltex.Width(txid), Ltex.Height(txid)/2, bposx, bposy)
	end

	return 0
end


--버튼을 그리는 약식함수(3종버튼 - 일반/롤오버/클릭)
---------------------------------------------------------------------
function triButtonDraw(txid, bposx, bposy, bwidth, bheight)

	if (mposx >=bposx+1) and (mposx <= bposx+bwidth-1) 
		and (mposy >=bposy+1) and  (mposy <=bposy+bheight-1) then 
		
		if mLb == 1 then Lsmd.Play(PlaySound[1], 0) end

		if mLb == 3 then		Ltex.Draw(txid, 0, bheight * 2, bwidth, bheight * 3 , bposx, bposy)			
		elseif mLb == 2 then	return 1
		else					Ltex.Draw(txid, 0, bheight * 1, bwidth, bheight * 2, bposx, bposy)	
		end
	else		
		Ltex.Draw(txid, 0, 0, bwidth, bheight * 1, bposx, bposy )  	
	end

	return 0
end


--타이머를 생성한다
-----------------------------------------
function SetTimer(_time, _min, _max, _add, _option)

	--1프레임딜레이값(최소1), 2카운터최소값, 3카운터최대값, 4.증감치, 5옵션(0;saw형, -1 or 1;wave형)
	local _timer = {}
	_timer["ct"] = _min
	_timer["time"] = _time
	_timer["min"] = _min
	_timer["max"] = _max
	_timer["add"] = _add

	if _option == nil then	_timer["opt"] = 0
	else					_timer["opt"] = _option
	end

	return _timer
end


--지정된 타이머의 값을 업데이트한다
------------------------------------------
function UpdateTimer(_timer)
	
	if (gBasicfct % _timer.time == 0) then		
		--saw형타이머 (1,2,3,4,1,2,3.........)
		if _timer.opt == 0 then		
			_timer.ct = _timer.ct + _timer.add
			if _timer.ct > _timer.max then --최대값에 도달
				_timer.ct = _timer.min	--최초값으로 리셋
				return 1
			end
		----------------------------------------------------------
		--wave형타이머 (1,2,3,4,3,2,1,2,.........)
		else
			if _timer.opt == 1 then	--수치증가중			
				_timer.ct = _timer.ct + _timer.add
				if _timer.ct > _timer.max then	--정점부이므로 감소시작
					_timer.ct = _timer.ct - 2
					_timer.opt = -1	--옵션값 수정
				end
			else				--수치감소중
				_timer.ct = _timer.ct - _timer.add
				if _timer.ct < _timer.min then	--정점부이므로 증가시작					
					_timer.ct = _timer.min	--최초값으로 리셋
					_timer.opt = 1			--옵션값 리셋
					return 1
				end
			end
		end
	end

	return 0
end


--초단위의 값을 받아 시:분:초 형식의 스트링으로 변환하는 함수
function GetStringTime(_sec)

	local _h1, h2, _m1, _m2, _s1, _s2

	_h1 = math.floor(_sec/3600)
	_h2 = _h1%10	; _h1 = math.floor(_h1/10)
	_m1 = math.floor((_sec%3600)/60)
	_m2 = _m1%10	; _m1 = math.floor(_m1/10)
	_s1 = _sec%60
	_s2 = _s1%10	; _s1 = math.floor(_s1/10)
	
	return string.format("%d%d:%d%d:%d%d", _h1, _h2, _m1, _m2, _s1, _s2)
end


--랜덤한 범위(_num1~_num2)의 수를 리턴하는 사용자 랜덤함수 _num1이 _num2보다 작아야함
function GetRandNum(_num1, _num2)

	local _randnum

	if _num1 == _num2 then _randnum = _num1
	else
		local _gap = math.abs(_num2 - _num1) + 1
		_randnum = (math.random(100000000)% _gap) + _num1
	end

	return _randnum
end


--테이블을 모두 뒤져서 해당조건에 맞는 값을 지닌 항목의 총수를 반환
function GetTableCount(_table, _num1, _num2)

	local _ct = 0
	local _totalct = 0
	while true do
		_ct = _ct + 1
		if (_table[_ct] == nil) then break end
		if (_table[_ct] >= _num1) and (_table[_ct] <= _num2) then
			_totalct = _totalct + 1
		end
	end

	return _totalct
end

--특정수치를 넣으면 텍스처폰트로 그려주는 함수(옵션은 정렬팩터 "left", "right")
function NumberToTexture(_num, _px, _py, _txid, _opt, _color, _scale)

	local _n = {}
	local _ct = 0
	--수를 각 자리수로 분해한다
	while true do
		_ct = _ct + 1
		_n[_ct] = math.floor(_num/(10^(_ct-1)))
		if _n[_ct] <= 0 then			--수치가 0일때
			if _ct == 1 then	_ct = _ct + 1	
			else				_n[_ct] = nil	--해당자리는 지움(0을 채우지 않는다)
			end
			break
		else
			_n[_ct] = _n[_ct]%10
		end
	end

	if _scale == nil then _scale = 1 end
	--화면출력	(그래픽폰트의 크기는 1문자당 10x12)
	local _gap = (Ltex.Width(_txid)/10) - 5
	--우측정렬시
	if _opt == "right" then
		for i=1, (_ct-1) do
				Ltex.Draw(_txid, 10*_n[i], 0, 10*(_n[i]+1), 12, _px-(i-1)*_gap, _py)
		end
	--좌측정렬시
	else
		for i=1, (_ct-1) do
			Ltex.Draw(_txid, 10*_n[_ct-i], 0, 10*(_n[_ct-i]+1), 12, _px+(i-1)*_gap, _py)
		end
	end

	return 0
end


--마우스 클릭후 업까지의 경로를 그린다
------------------------------------------------------------
function TapLineDraw(axisfact, movefact, direct_x, direct_y, downposx, downposy,  upposx, upposy)
	
	if axisfact == -1 then	--x축 이동폭이 더 큼 (기준팩터 y)
		--마우스이동경로를 픽셀단위로 찍는다
		for j=1, 140 do	
			if downposx + direct_x * ((j-1)*movefact) == (upposx) then  return	end
			for i=1, math.floor(movefact) do
				if downposx + direct_x * ((j-1)*movefact +(i-1)) == (upposx) then  return	end
				Ltex.Draw(tx_source[14], 0, 0, 1, 1, 
							downposx + direct_x * ((j-1)*movefact +(i-1)), 
							downposy + direct_y * (j-1))
			end
		end

	else							--y축 이동폭이 더 큼 (기준팩터 x)
		--마우스이동경로를 픽셀단위로 찍는다
		for j=1, 140 do
			if downposy + direct_y * ((j-1)*movefact) == upposy then	return end
			for i=1, math.floor(movefact) do
				if downposy + direct_y * ((j-1)*movefact +(i-1)) == upposy then	return	end
				Ltex.Draw(tx_source[14], 0, 0, 1, 1, 
							downposx + direct_x * (j-1), 
							downposy + direct_y * ((j-1)*movefact +(i-1)))
			end
		end
	end

	return 0
end

--마우스 클릭후 업까지의 경로를 계산한다
------------------------------------------------------------
function TapLineCheck(x_down, y_down, x_up, y_up)

	--거리값 구하기(강도 측정용)
	local length = ( (x_up - x_down)^2 ) + ( (y_up - y_down)^2 )
	length = math.floor( math.sqrt(length) /2 )

	--x,y 방향성 체크
	local direction_x = 1  
	local direction_y = 1
	
	if y_down > y_up then		direction_y = -1	end
	if x_down > x_up then		direction_x = -1	end

	--이동값펙터 
	local mfact , maxis
	if math.abs(x_down - x_up) - math.abs(y_down - y_up) >= 0 then		--x축 증가폭이 크다면
		if (y_down - y_up) == 0  then --변칙적인 예외사항 피하기
			mfact = 150; 		maxis = -1 ; direction_y = 0				
		else 		
			mfact = (x_down - x_up) / (y_down - y_up)
			maxis = -1
		end		
	
	elseif math.abs(x_down - x_up) - math.abs(y_down - y_up) < 0 then		--y축 증가폭이 크다면
		if (x_down - x_up) == 0 then --변칙적인 예외사항 피하기
			mfact = 150;		maxis = 1; direction_x = 0 
		else		
			mfact = (y_down - y_up) / (x_down - x_up) 
			maxis = 1
		end		
	end	

	return maxis, math.abs((mfact)), length, direction_x, direction_y
end


--페이드 인/아웃을 가동하는 함수
-------------------------------------------------------------------
function Draw_swapfx(_posx, _posy, _width, _height)

	local _alpha = (tFade.ct-1)*2
	Ltex.Draw(tx_title[1], 0, 0, 320, 240, 0, 0, 1, 1, string.format("0x%X%XFFFFFF", _alpha, _alpha))

	return 0
end

function PageSwap(_next)

	gPageSwapOn = true
	gNextPage = _next
	tFade = SetTimer(1, 1, 8, 1, 1)	--화면전환(페이드i/o)타이머 세팅

	return 0
end

function MapSwap(_next)

	gMapSwapOn = true
	gNextMap = _next
	tFade = SetTimer(1, 1, 8, 1, 1)	--화면전환(페이드i/o)타이머 세팅

	return 0
end

--테이블을 읽어들인후 파일(csv or tab-text)로 저장한다(_opt = ",", "\t")
-----------------------------------------------------------------
function SaveFile(_table, _file, _opt)

	local savefile = Lsys.Open(_file ,"w")
	local _ct1 = 1

	while true do

		local _ct2 = 1
		if _table[_ct1][_ct2] == nil then break end
		
		while true do
			if _table[_ct1][_ct2+1] == nil then
				savefile:write(_table[_ct1][_ct2], "\n")	--행의 끝
				break
			else
				savefile:write(_table[_ct1][_ct2], _opt)
			end
			_ct2 = _ct2 + 1
		end
		_ct1 = _ct1 + 1
	end

	savefile:close()

	return	0
end

--파일(csv or tab-text)을 읽어들인후 테이블로 전환 리턴(_opt = ",", "\t")
function GetFile(_file, _opt)

	local _table = {}

	local fileset = Lsys.Open(_file)
	local _ct1 = 1
	
	while true do
		
		_table[_ct1] = {}

		local _line	=  fileset:read()	--1라인씩 temp에 읽어들인다
		local _ct2 = 0 
		local _comma = 0 ; local _begin = 1

		if _line == nil then  
			_table[_ct1] = nil ; break
		end
		---------------------------------------------------------------------------------------
		while true do
			_comma = string.find(_line, _opt, _comma+1)	--","or "\t"의 위치를 찾아 저장
			_ct2 = _ct2 + 1

			if _comma == nil then		--더이상 ","를 찾을 수 없음(행의 끝)
				_table[_ct1][_ct2] = string.sub(_line, _begin, string.len(_line))	--이전최종위치에서 행끝까지를 테이블에저장
				if tonumber(_table[_ct1][_ct2]) then							--number형식의 문자열이면 number로 변환
					_table[_ct1][_ct2] = tonumber(_table[_ct1][_ct2])
				end
				break 
			else
				_table[_ct1][_ct2] = string.sub(_line, _begin, _comma-1)	--이전위치에서 컴마위치 -1까지 테이블에저장(,제외)
				if tonumber(_table[_ct1][_ct2]) then							--number형식의 문자열이면 number로 변환
					_table[_ct1][_ct2] = tonumber(_table[_ct1][_ct2])
				end
				_begin = _comma+1	--위치 업데이트
			end
		end
		---------------------------------------------------------------------------------------
		_ct1 = _ct1 + 1
	end

	fileset:close()

	return _table
end


--파일(csv or tab-text)을 읽어들인후 테이블로 전환 리턴(자동 템플릿 버전; 최초 1행은 자동테이블인덱스가 된다)
function GetFileWithIndex(_csvfile, _opt)

	local _table = {}
	local fileset = Lsys.Open(_csvfile)
	local _ct1 = 0
	local _index = {}
	
	while true do
		
		if _ct1 > 0 then _table[_ct1] = {} end
		local _line	=  fileset:read()	--1라인씩 temp에 읽어들인다
		local _ct2 = 0 
		local _comma = 0 ; local _begin = 1

		if _line == nil then  
			_table[_ct1] = nil ; break
		end
		---------------------------------------------------------------------------------------
		while true do
			_comma = string.find(_line, _opt, _comma+1)	--",""\t"의 위치를 찾아 저장
			_ct2 = _ct2 + 1

			if _comma == nil then		--더이상 ",""\t"를 찾을 수 없음(행의 끝)
				if _ct1 > 0 then 
					_table[_ct1][_index[_ct2]] = string.sub(_line, _begin, string.len(_line))	--이전최종위치에서 행끝까지를 테이블에저장
					if tonumber(_table[_ct1][_index[_ct2]]) then							--number형식의 문자열이면 number로 변환
						_table[_ct1][_index[_ct2]] = tonumber(_table[_ct1][_index[_ct2]])
					end
				else	--메인테이블이 아닌 인덱스테이블에 저장(최초1행)
					_index[_ct2] = string.sub(_line, _begin, string.len(_line))
				end
				break 
			else
				if _ct1 > 0 then
					_table[_ct1][_index[_ct2]] = string.sub(_line, _begin, _comma-1)	--이전위치에서 컴마위치 -1까지 테이블에저장(,제외)
					if tonumber(_table[_ct1][_index[_ct2]]) then							--number형식의 문자열이면 number로 변환
						_table[_ct1][_index[_ct2]] = tonumber(_table[_ct1][_index[_ct2]])
					end					
				else	--메인테이블이 아닌 인덱스테이블에 저장(최초1행)
					_index[_ct2] = string.sub(_line, _begin, _comma-1)
				end
				_begin = _comma + 1	--위치 업데이트
			end
		end
		---------------------------------------------------------------------------------------
		_ct1 = _ct1 + 1
	end

	fileset:close()

	return _table
end


