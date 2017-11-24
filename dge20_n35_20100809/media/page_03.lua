
-- �ʼ��⺻ ������ �ҷ��´�.
-----------------------------------------------------------------------
function Set_varible()

	CurTime = 0; 	STimer = 0		--������Ÿ�� ���غ���
	mposx = 0; mposy = 0			--���콺X,y��ǥ
	mLb = 0; mRb= 0; mMb = 0		--���콺 ��ư

	Key = {}				--Ű���� �Է�
	for i = 1,256 do		Key[i] = 0	end

	gCurpage = 0			--���� ������ (0; Ÿ��Ʋ, 1;������������, 2;�����÷���, 3;�������, 4;����/����)
	gNextPage = 0			--���� ������(��������ȯ�� ���)
	gBasicfct = 0			-- +1�Ϲ� ���� ī����(�����ӱ��� 10)

	shim = 0		--�����/üũ�� ����

	return 0
end

-- �⺻���� ����( 1.Ÿ�̸�, 2. ���콺, 3.Ű����)
-------------------------------------------------------------------------------
function Set_input()

	--1. Ÿ�̸�
	CurTime = Lsys.GetTickCount()						--ms(�и�������)

	--2. ���콺
	mposx, mposy, mposz = Lin.MousePos()		-- ���콺 ������
	mLb, mRb, mMb = Lin.MouseEvnt()				-- ���콺 �̺�Ʈ(0:�Է¾���,1:Down,3:Pressed)

	--3. Ű����
	for i=1,256 do	 --9(TAB), 13(����), 27(ESC), 32(SPACE), 33(PAGEUP), 38(CUR-UP), 49~(1), 65~(A), 112~(F1)
		Key[i] = Lin.KeyboardOne(i)					-- Ű���� �̺�Ʈ(0:�Է¾���,1:Down,3:Pressed)
	end

	return 0
end

--[�浹1] ��(point)�� ����(rect)�� üũ
---------------------------------------------------------------------------
function PointInRect(_px, _py, _rx, _ry, _rw, _rh)

	if (_px >= _rx) and (_px <= _rx + _rw) and
		(_py >= _ry) and (_py <= _ry + _rh)
		then
			
		return 1
	end

	return 0
end

--[�浹2] ��(point)�� ����(circle)�� �浹üũ
---------------------------------------------------------------------------
function PointInCircle(_px, _py, _cx, _cy, _cr)
	
	if ((_cr^2) >= ((_cx - _px)^2)+((_cy - _py)^2) ) 
		then

		return 1
	end

	return 0
end

--[�浹3] ����(rect1)�� ����(rect2)���� �浹 üũ 
---------------------------------------------------------------------------
function RectInRect(_r1px, _r1py, _r1w, _r1h, _r2px, _r2py, _r2w, _r2h)

	--r1�� �»��x�� r2���ϴ�x���� �۴�	_r1px <= _r2px+_r2w
	--r1�� �»��y�� r2���ϴ�y���� �۴� _r1py <= _r2py+_r2h
	--r1�� ���ϴ�x�� r2�»��x���� ũ�� _r1px+_r1w >= _r2px
	--r1�� ���ϴ�y�� r2�»��y���� ũ�� _r1py+_r1h >= _r2py

	if (_r1px <= _r2px+_r2w) and (_r1py <= _r2py+_r2h) and
		(_r1px+_r1w >= _r2px) and (_r1py+_r1h >= _r2py) then			
		return 1
	end

	return 0
end

--[�浹4] ��-�� ���� �浹 üũ (c1�� �»����ǥ, c1�ؽ�ó width, c2�� �»����ǥ, c2�ؽ�ó width)
---------------------------------------------------------------------------
function CircleInCircle(c1posx, c1posy, c1width, c2posx, c2posy, c2width)

	--c1, c2�� ����������
	local c1r, c2r
	c1r = c1width/2
	c2r = c2width/2

	--c1, c2�� �߽���ǥ����
	local c1x, c1y, c2x, c2y
	c1x = c1posx + c1r ; 	c1y = c1posy + c1r
	c2x = c2posx + c2r ; 	c2y = c2posy + c2r

	--c1, c2�� �߽��� ������ �Ÿ�����
	local xx = ((c2x - c1x)^2) + ((c2y - c1y)^2)
	xx = math.sqrt(xx)
	
	--�߽ɰ��Ÿ�(xx)�� c1, c2 �������� �պ��� ������ �ο��� ��������(return 1)
	if ( xx <= (c1r+c2r) ) then
		return 1
	end

	return 0
end


--��ư�� �׸��� ����Լ�(2����ư- �Ϲ�/Ŭ��)
---------------------------------------------------------------------
function byButtonDraw(txid, bposx, bposy, bwidth, bheight)

	if (mposx >= bposx) and (mposx <= bposx + bwidth) and
		(mposy >= bposy) and (mposy <= bposy + bheight)		then
			
		--��ư �ѿ��� or Ŭ��
		Ltex.Draw(txid, 0, Ltex.Height(txid)/2, Ltex.Width(txid), Ltex.Height(txid), bposx, bposy)

		if mLb == 1 then Lsmd.Play(PlaySound[1], 0) end

		if (mLb == 2) then		return 2
		else					return 1
		end		

	else
		--��ư �Ϲݻ���
		Ltex.Draw(txid, 0, 0, Ltex.Width(txid), Ltex.Height(txid)/2, bposx, bposy)
	end

	return 0
end


--��ư�� �׸��� ����Լ�(3����ư - �Ϲ�/�ѿ���/Ŭ��)
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


--Ÿ�̸Ӹ� �����Ѵ�
-----------------------------------------
function SetTimer(_time, _min, _max, _add, _option)

	--1�����ӵ����̰�(�ּ�1), 2ī�����ּҰ�, 3ī�����ִ밪, 4.����ġ, 5�ɼ�(0;saw��, -1 or 1;wave��)
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


--������ Ÿ�̸��� ���� ������Ʈ�Ѵ�
------------------------------------------
function UpdateTimer(_timer)
	
	if (gBasicfct % _timer.time == 0) then		
		--saw��Ÿ�̸� (1,2,3,4,1,2,3.........)
		if _timer.opt == 0 then		
			_timer.ct = _timer.ct + _timer.add
			if _timer.ct > _timer.max then --�ִ밪�� ����
				_timer.ct = _timer.min	--���ʰ����� ����
				return 1
			end
		----------------------------------------------------------
		--wave��Ÿ�̸� (1,2,3,4,3,2,1,2,.........)
		else
			if _timer.opt == 1 then	--��ġ������			
				_timer.ct = _timer.ct + _timer.add
				if _timer.ct > _timer.max then	--�������̹Ƿ� ���ҽ���
					_timer.ct = _timer.ct - 2
					_timer.opt = -1	--�ɼǰ� ����
				end
			else				--��ġ������
				_timer.ct = _timer.ct - _timer.add
				if _timer.ct < _timer.min then	--�������̹Ƿ� ��������					
					_timer.ct = _timer.min	--���ʰ����� ����
					_timer.opt = 1			--�ɼǰ� ����
					return 1
				end
			end
		end
	end

	return 0
end


--�ʴ����� ���� �޾� ��:��:�� ������ ��Ʈ������ ��ȯ�ϴ� �Լ�
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


--������ ����(_num1~_num2)�� ���� �����ϴ� ����� �����Լ� _num1�� _num2���� �۾ƾ���
function GetRandNum(_num1, _num2)

	local _randnum

	if _num1 == _num2 then _randnum = _num1
	else
		local _gap = math.abs(_num2 - _num1) + 1
		_randnum = (math.random(100000000)% _gap) + _num1
	end

	return _randnum
end


--���̺��� ��� ������ �ش����ǿ� �´� ���� ���� �׸��� �Ѽ��� ��ȯ
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

--Ư����ġ�� ������ �ؽ�ó��Ʈ�� �׷��ִ� �Լ�(�ɼ��� �������� "left", "right")
function NumberToTexture(_num, _px, _py, _txid, _opt, _color, _scale)

	local _n = {}
	local _ct = 0
	--���� �� �ڸ����� �����Ѵ�
	while true do
		_ct = _ct + 1
		_n[_ct] = math.floor(_num/(10^(_ct-1)))
		if _n[_ct] <= 0 then			--��ġ�� 0�϶�
			if _ct == 1 then	_ct = _ct + 1	
			else				_n[_ct] = nil	--�ش��ڸ��� ����(0�� ä���� �ʴ´�)
			end
			break
		else
			_n[_ct] = _n[_ct]%10
		end
	end

	if _scale == nil then _scale = 1 end
	--ȭ�����	(�׷�����Ʈ�� ũ��� 1���ڴ� 10x12)
	local _gap = (Ltex.Width(_txid)/10) - 5
	--�������Ľ�
	if _opt == "right" then
		for i=1, (_ct-1) do
				Ltex.Draw(_txid, 10*_n[i], 0, 10*(_n[i]+1), 12, _px-(i-1)*_gap, _py)
		end
	--�������Ľ�
	else
		for i=1, (_ct-1) do
			Ltex.Draw(_txid, 10*_n[_ct-i], 0, 10*(_n[_ct-i]+1), 12, _px+(i-1)*_gap, _py)
		end
	end

	return 0
end


--���콺 Ŭ���� �������� ��θ� �׸���
------------------------------------------------------------
function TapLineDraw(axisfact, movefact, direct_x, direct_y, downposx, downposy,  upposx, upposy)
	
	if axisfact == -1 then	--x�� �̵����� �� ŭ (�������� y)
		--���콺�̵���θ� �ȼ������� ��´�
		for j=1, 140 do	
			if downposx + direct_x * ((j-1)*movefact) == (upposx) then  return	end
			for i=1, math.floor(movefact) do
				if downposx + direct_x * ((j-1)*movefact +(i-1)) == (upposx) then  return	end
				Ltex.Draw(tx_source[14], 0, 0, 1, 1, 
							downposx + direct_x * ((j-1)*movefact +(i-1)), 
							downposy + direct_y * (j-1))
			end
		end

	else							--y�� �̵����� �� ŭ (�������� x)
		--���콺�̵���θ� �ȼ������� ��´�
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

--���콺 Ŭ���� �������� ��θ� ����Ѵ�
------------------------------------------------------------
function TapLineCheck(x_down, y_down, x_up, y_up)

	--�Ÿ��� ���ϱ�(���� ������)
	local length = ( (x_up - x_down)^2 ) + ( (y_up - y_down)^2 )
	length = math.floor( math.sqrt(length) /2 )

	--x,y ���⼺ üũ
	local direction_x = 1  
	local direction_y = 1
	
	if y_down > y_up then		direction_y = -1	end
	if x_down > x_up then		direction_x = -1	end

	--�̵������� 
	local mfact , maxis
	if math.abs(x_down - x_up) - math.abs(y_down - y_up) >= 0 then		--x�� �������� ũ�ٸ�
		if (y_down - y_up) == 0  then --��Ģ���� ���ܻ��� ���ϱ�
			mfact = 150; 		maxis = -1 ; direction_y = 0				
		else 		
			mfact = (x_down - x_up) / (y_down - y_up)
			maxis = -1
		end		
	
	elseif math.abs(x_down - x_up) - math.abs(y_down - y_up) < 0 then		--y�� �������� ũ�ٸ�
		if (x_down - x_up) == 0 then --��Ģ���� ���ܻ��� ���ϱ�
			mfact = 150;		maxis = 1; direction_x = 0 
		else		
			mfact = (y_down - y_up) / (x_down - x_up) 
			maxis = 1
		end		
	end	

	return maxis, math.abs((mfact)), length, direction_x, direction_y
end


--���̵� ��/�ƿ��� �����ϴ� �Լ�
-------------------------------------------------------------------
function Draw_swapfx(_posx, _posy, _width, _height)

	local _alpha = (tFade.ct-1)*2
	Ltex.Draw(tx_title[1], 0, 0, 320, 240, 0, 0, 1, 1, string.format("0x%X%XFFFFFF", _alpha, _alpha))

	return 0
end

function PageSwap(_next)

	gPageSwapOn = true
	gNextPage = _next
	tFade = SetTimer(1, 1, 8, 1, 1)	--ȭ����ȯ(���̵�i/o)Ÿ�̸� ����

	return 0
end

function MapSwap(_next)

	gMapSwapOn = true
	gNextMap = _next
	tFade = SetTimer(1, 1, 8, 1, 1)	--ȭ����ȯ(���̵�i/o)Ÿ�̸� ����

	return 0
end

--���̺��� �о������ ����(csv or tab-text)�� �����Ѵ�(_opt = ",", "\t")
-----------------------------------------------------------------
function SaveFile(_table, _file, _opt)

	local savefile = Lsys.Open(_file ,"w")
	local _ct1 = 1

	while true do

		local _ct2 = 1
		if _table[_ct1][_ct2] == nil then break end
		
		while true do
			if _table[_ct1][_ct2+1] == nil then
				savefile:write(_table[_ct1][_ct2], "\n")	--���� ��
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

--����(csv or tab-text)�� �о������ ���̺�� ��ȯ ����(_opt = ",", "\t")
function GetFile(_file, _opt)

	local _table = {}

	local fileset = Lsys.Open(_file)
	local _ct1 = 1
	
	while true do
		
		_table[_ct1] = {}

		local _line	=  fileset:read()	--1���ξ� temp�� �о���δ�
		local _ct2 = 0 
		local _comma = 0 ; local _begin = 1

		if _line == nil then  
			_table[_ct1] = nil ; break
		end
		---------------------------------------------------------------------------------------
		while true do
			_comma = string.find(_line, _opt, _comma+1)	--","or "\t"�� ��ġ�� ã�� ����
			_ct2 = _ct2 + 1

			if _comma == nil then		--���̻� ","�� ã�� �� ����(���� ��)
				_table[_ct1][_ct2] = string.sub(_line, _begin, string.len(_line))	--����������ġ���� �ೡ������ ���̺�����
				if tonumber(_table[_ct1][_ct2]) then							--number������ ���ڿ��̸� number�� ��ȯ
					_table[_ct1][_ct2] = tonumber(_table[_ct1][_ct2])
				end
				break 
			else
				_table[_ct1][_ct2] = string.sub(_line, _begin, _comma-1)	--������ġ���� �ĸ���ġ -1���� ���̺�����(,����)
				if tonumber(_table[_ct1][_ct2]) then							--number������ ���ڿ��̸� number�� ��ȯ
					_table[_ct1][_ct2] = tonumber(_table[_ct1][_ct2])
				end
				_begin = _comma+1	--��ġ ������Ʈ
			end
		end
		---------------------------------------------------------------------------------------
		_ct1 = _ct1 + 1
	end

	fileset:close()

	return _table
end


--����(csv or tab-text)�� �о������ ���̺�� ��ȯ ����(�ڵ� ���ø� ����; ���� 1���� �ڵ����̺��ε����� �ȴ�)
function GetFileWithIndex(_csvfile, _opt)

	local _table = {}
	local fileset = Lsys.Open(_csvfile)
	local _ct1 = 0
	local _index = {}
	
	while true do
		
		if _ct1 > 0 then _table[_ct1] = {} end
		local _line	=  fileset:read()	--1���ξ� temp�� �о���δ�
		local _ct2 = 0 
		local _comma = 0 ; local _begin = 1

		if _line == nil then  
			_table[_ct1] = nil ; break
		end
		---------------------------------------------------------------------------------------
		while true do
			_comma = string.find(_line, _opt, _comma+1)	--",""\t"�� ��ġ�� ã�� ����
			_ct2 = _ct2 + 1

			if _comma == nil then		--���̻� ",""\t"�� ã�� �� ����(���� ��)
				if _ct1 > 0 then 
					_table[_ct1][_index[_ct2]] = string.sub(_line, _begin, string.len(_line))	--����������ġ���� �ೡ������ ���̺�����
					if tonumber(_table[_ct1][_index[_ct2]]) then							--number������ ���ڿ��̸� number�� ��ȯ
						_table[_ct1][_index[_ct2]] = tonumber(_table[_ct1][_index[_ct2]])
					end
				else	--�������̺��� �ƴ� �ε������̺� ����(����1��)
					_index[_ct2] = string.sub(_line, _begin, string.len(_line))
				end
				break 
			else
				if _ct1 > 0 then
					_table[_ct1][_index[_ct2]] = string.sub(_line, _begin, _comma-1)	--������ġ���� �ĸ���ġ -1���� ���̺�����(,����)
					if tonumber(_table[_ct1][_index[_ct2]]) then							--number������ ���ڿ��̸� number�� ��ȯ
						_table[_ct1][_index[_ct2]] = tonumber(_table[_ct1][_index[_ct2]])
					end					
				else	--�������̺��� �ƴ� �ε������̺� ����(����1��)
					_index[_ct2] = string.sub(_line, _begin, _comma-1)
				end
				_begin = _comma + 1	--��ġ ������Ʈ
			end
		end
		---------------------------------------------------------------------------------------
		_ct1 = _ct1 + 1
	end

	fileset:close()

	return _table
end


