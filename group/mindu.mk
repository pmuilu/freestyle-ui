# ============================================================================
#  Name	 : Icons_scalable_dc.mk
#  Part of  : Contacts
#
#  Description: This is file for creating .mif file (scalable icon)
# 
# ============================================================================


ZDIR=$(EPOCROOT)epoc32\release\winscw\udeb\Z

TARGETDIR=$(ZDIR)\resource\apps
ICONTARGETFILENAME=$(TARGETDIR)\theme_mindu_synble.mif

ICONDIR=..\data\mindu

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : 
	del $(ICONTARGETFILENAME)

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : $(ICONTARGETFILENAME)

$(ICONTARGETFILENAME) : $(ICONDIR)\toggle_options.svg
	mifconv $(ICONTARGETFILENAME) /c32 $(ICONDIR)\toggle_options.svg	\
		/c32 $(ICONDIR)\background.svg	\
		/c32 $(ICONDIR)\toggle_switch.svg	\
		/c32 $(ICONDIR)\linebackground.svg	\
		/c32 $(ICONDIR)\radiobutton_selected.svg	\
		/c32 $(ICONDIR)\radiobutton_unselected.svg	\
		/c32 $(ICONDIR)\checkbox_checked.svg	\
		/c32 $(ICONDIR)\checkbox_unchecked.svg	\
		/c32 $(ICONDIR)\abc_uppercase.svg	\
		/htheme.mbg

FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(ICONTARGETFILENAME)

FINAL : do_nothing
