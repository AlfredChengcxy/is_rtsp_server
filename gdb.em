macro GDB_BreakFunc_Add()
{
	hwnd= GetCurrentWnd()
	if(hwnd==0)
		stop
	sel= GetWndSel(hwnd)
	hbuf= GetWndBuf(hwnd)
//	file_name= GDB_GetFileName(GetBufName(hbuf))

	gdb_hbuf= GDB_OpenFile()
	
	gdb_brk_cmd= GDB_GetBreakFuncCmd(hbuf, gdb_hbuf)
	var gdb_brk_cmd2
	if(gdb_brk_cmd!= ""){
		gdb_brk_cmd2= cat("#", gdb_brk_cmd)
	}
	else{
		return
	}
	
	GDB_BreakPointsUpdate(gdb_hbuf, gdb_brk_cmd, gdb_brk_cmd2, 1)
	
	GDB_CloseFile(gdb_hbuf)
}

macro GDB_BreakFunc_Remove()
{	
	hwnd= GetCurrentWnd()
	if(hwnd==0)
		stop
	sel= GetWndSel(hwnd)
	hbuf= GetWndBuf(hwnd)

	gdb_hbuf= GDB_OpenFile()
	
	gdb_brk_cmd= GDB_GetBreakFuncCmd(hbuf, gdb_hbuf)
	var gdb_brk_cmd2
	if(gdb_brk_cmd!= ""){
		gdb_brk_cmd2= cat("#", gdb_brk_cmd)
	}
	else
		return
	
	GDB_BreakPointsUpdate(gdb_hbuf, gdb_brk_cmd, gdb_brk_cmd2, 0)
	
	GDB_CloseFile(gdb_hbuf)
}

macro GDB_BreakLine_Add()
{
	hwnd= GetCurrentWnd()
	if(hwnd==0)
		stop
	sel= GetWndSel(hwnd)
	hbuf= GetWndBuf(hwnd)

	gdb_hbuf= GDB_OpenFile()
	
	gdb_brk_cmd= GDB_GetBreakLineCmd(hbuf, gdb_hbuf)
	gdb_brk_cmd2= cat("#", gdb_brk_cmd)
	
	GDB_BreakPointsUpdate(gdb_hbuf, gdb_brk_cmd, gdb_brk_cmd2, 1)
	
	GDB_CloseFile(gdb_hbuf)
}

macro GDB_BreakLine_Remove()
{
	hwnd= GetCurrentWnd()
	if(hwnd==0)
		stop
	sel= GetWndSel(hwnd)
	hbuf= GetWndBuf(hwnd)

	gdb_hbuf= GDB_OpenFile()
	gdb_brk_cmd= GDB_GetBreakLineCmd(hbuf, gdb_hbuf)
	gdb_brk_cmd2= cat("#", gdb_brk_cmd)
	
	GDB_BreakPointsUpdate(gdb_hbuf, gdb_brk_cmd, gdb_brk_cmd2, 0)
	
	GDB_CloseFile(gdb_hbuf)
}

macro GDB_BreakLine_AllRemove()
{
	gdb_hbuf= GDB_OpenFile()

	hwnd= GetCurrentWnd()
	if(hwnd==0)
		stop
	sel= GetWndSel(hwnd)
	hbuf= GetWndBuf(hwnd)
	
	gdb_line_cnt= GetBufLineCount(gdb_hbuf)
	while(gdb_line_cnt--!= 0)
	{
		tmp_cmd= GetBufLine(gdb_hbuf, gdb_line_cnt)
		
		tLen= strlen(tmp_cmd)
		if(tLen> 5)
			tmp_cmd2= strmid(tmp_cmd, 0, 6)
		else
			continue
			
		if((tmp_cmd2== "break "){
			DelBufLine(gdb_hbuf, gdb_line_cnt)
			tmp_cmd= cat("#", tmp_cmd)
			InsBufLine(gdb_hbuf, gdb_line_cnt, tmp_cmd)
		}
	}
	
	SaveBuf(gdb_hbuf)
	GDB_CloseFile(gdb_hbuf)
}

macro GDB_OpenFile()
{
	return OpenBuf("gdb_break.ini")
}

macro GDB_CloseFile(hbuf)
{
	return CloseBuf(hbuf)
}

macro GDB_BreakPointsUpdate(gdb_hbuf, cmd0, cmd1, flag)
{
	gdb_line_cnt= GetBufLineCount(gdb_hbuf)
	break_hit= 0
	while(gdb_line_cnt--!= 0)
	{
		tmp_cmd= GetBufLine(gdb_hbuf, gdb_line_cnt)
		
		if((tmp_cmd== cmd0) || (tmp_cmd== cmd1)){
			DelBufLine(gdb_hbuf, gdb_line_cnt)
			if(flag== 0)
				InsBufLine(gdb_hbuf, gdb_line_cnt, cmd1)
			else
				InsBufLine(gdb_hbuf, gdb_line_cnt, cmd0)
			break_hit= 1
			break
		}
		else{
			continue
		}
	}
	
	if(break_hit== 0){
		if(flag== 0)
			InsBufLine(gdb_hbuf, 0, cmd1)
		else
			InsBufLine(gdb_hbuf, 0, cmd0)
	}
	
	SaveBuf(gdb_hbuf)
}

macro GDB_GetBreakLineCmd(hbuf, gdb_hbuf)
{
	hprj= GetCurrentProj()
	prj_dir= GetProjDir(hprj)
	
	file_name= GetBufName(hbuf)
	start_index= strlen(prj_dir)+ 1
	prj_file_name= strmid(file_name, start_index, strlen(file_name))
	prj_file_name= GDB_PathDos2Unix(prj_file_name)
		
	cur_line= GetBufLnCur(hbuf)+ 1
	
	gdb_brk_cmd= "break "
	gdb_brk_cmd= cat(gdb_brk_cmd, prj_file_name)
	gdb_brk_cmd= cat(gdb_brk_cmd, ":")
	gdb_brk_cmd= cat(gdb_brk_cmd, cur_line)
	
	return gdb_brk_cmd
}

macro GDB_GetBreakFuncCmd(hbuf, gdb_hbuf)
{
	hprj= GetCurrentProj()
	prj_dir= GetProjDir(hprj)
	
	file_name= GetBufName(hbuf)
	start_index= strlen(prj_dir)+ 1
	prj_file_name= strmid(file_name, start_index, strlen(file_name))
	prj_file_name= GDB_PathDos2Unix(prj_file_name)
		
	func_symbol= GetCurSymbol()
	if(func_symbol== "")
		return ""
	
	gdb_brk_cmd= "break "
	gdb_brk_cmd= cat(gdb_brk_cmd, prj_file_name)
	gdb_brk_cmd= cat(gdb_brk_cmd, ":")
	gdb_brk_cmd= cat(gdb_brk_cmd, func_symbol)

	return gdb_brk_cmd
}

macro GDB_GetFileName(sz)
{
    i = 1
    szName = sz
    iLen = strlen(sz)
    if(iLen == 0)
      return ""
    while( i <= iLen)
    {
      if(sz[iLen-i] == "\\")
      {
        szName = strmid(sz,iLen-i+1,iLen)
        break
      }
      i = i + 1
    }
    return szName
}

macro GDB_PathDos2Unix(sz)
{
    i = 1
    szName = sz
    iLen = strlen(sz)
    if(iLen == 0)
      return ""
	  
    while( i <= iLen)
    {
	if(sz[iLen-i] == "\\"){
		szName[iLen-i] = "\/"
	}
      i = i + 1
    }
    return szName
}