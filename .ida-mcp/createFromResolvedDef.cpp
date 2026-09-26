// C++ exceptions not shown because they made the function too large
std::shared_ptr<UIControl> *__fastcall UIControlFactory::_createFromResolvedDef(
        UIResolvedDef *result,
        const UIControlFactoryContext *context,
        const UIResolvedDef *resolvedDef,
        UIResolvedDef *a4,
        UIControl *a5,
        std::_Ref_count_base *a6,
        ui::ChildInsertPosition a7,
        char a8)
{
  const UIControlFactoryContext *v9; // rsi
  UIControl *v10; // rsi
  volatile signed __int32 *v11; // rcx
  volatile signed __int32 *v12; // rdi
  std::string::assign::<lambda_1> v13; // r8
  std::_Ref_count_base *v14; // rax
  unsigned __int64 Mysize; // rsi
  const std::string *p_mDefName; // r9
  std::string *Ptr; // rcx
  unsigned __int64 v18; // rax
  std::string *p_mName; // rdi
  unsigned __int64 Myres; // rax
  char *v21; // rax
  void *v22; // rcx
  unsigned __int64 v23; // rdx
  UIResolvedDef *v24; // rsi
  __m128i *v25; // rdi
  std::string::append::<lambda_1> v26; // r8
  __int64 v27; // rbx
  const __m128i *p_defaultValue; // rax
  __m128i v29; // xmm0
  UIResolvedDef *v30; // rdi
  size_t v31; // rsi
  size_t *v32; // rax
  size_t *v33; // rbx
  char *v34; // rsi
  void *v35; // rcx
  unsigned __int64 v36; // rdx
  void *v37; // rcx
  unsigned __int64 v38; // rdx
  void *v39; // rcx
  unsigned __int64 v40; // rdx
  __int64 v41; // rax
  UIResolvedDef *v42; // rdi
  UIControl *v43; // rsi
  UIControl *v44; // rdi
  __int64 v45; // rdx
  char *v46; // rsi
  std::unique_ptr<StructureFeature> *v47; // r15
  unsigned __int64 v48; // rdi
  StructureFeature *v49; // rax
  unsigned __int64 v50; // rdx
  unsigned __int64 v51; // r14
  std::unique_ptr<StructureFeature> *v52; // rbx
  RenderableComponent *v53; // rdi
  unsigned __int8 v54; // r15
  unsigned __int8 v55; // al
  RenderableComponent **v56; // rcx
  RenderableComponent **v57; // r8
  UIControl *v58; // rdi
  __int64 v59; // rdx
  UIResolvedDef *v60; // rsi
  unsigned __int64 v61; // rdi
  unsigned __int64 v62; // rax
  unsigned __int64 v63; // rcx
  unsigned __int64 v64; // rsi
  std::vector<std::unique_ptr<UIComponent>> *v65; // rbx
  UIResolvedDef *v66; // r14
  RenderableComponent *v67; // rdi
  unsigned __int8 v68; // r14
  unsigned __int8 v69; // al
  RenderableComponent **v70; // rcx
  RenderableComponent **v71; // r8
  UIControl *v72; // rdi
  __int64 v73; // rdx
  char *v74; // rsi
  std::unique_ptr<StructureFeature> *v75; // r15
  unsigned __int64 v76; // rdi
  StructureFeature *v77; // rax
  unsigned __int64 v78; // rdx
  unsigned __int64 v79; // r14
  std::unique_ptr<StructureFeature> *v80; // rbx
  RenderableComponent *v81; // rdi
  unsigned __int8 v82; // r15
  unsigned __int8 v83; // al
  RenderableComponent **v84; // rcx
  RenderableComponent **v85; // r8
  UIResolvedDef *v86; // rdi
  UIControl *v87; // rsi
  __int64 v88; // rdx
  UIControl *v89; // rsi
  unsigned __int64 v90; // rdi
  unsigned __int64 v91; // rax
  unsigned __int64 v92; // rdx
  unsigned __int64 v93; // rsi
  std::vector<std::unique_ptr<UIComponent>> *p_mComponents; // rbx
  RuinedPortalFeature *v95; // r14
  RenderableComponent *v96; // rdi
  unsigned __int8 v97; // r14
  unsigned __int8 v98; // al
  RenderableComponent **v99; // rcx
  RenderableComponent **v100; // r8
  UIControl *v101; // rdi
  __int64 v102; // rdx
  UIResolvedDef *v103; // rsi
  UIControl *v104; // rcx
  UIPropertyBag *PropertyBag; // rax
  __int64 v106; // rdi
  unsigned __int64 v107; // rax
  unsigned __int64 v108; // r8
  unsigned __int64 v109; // rsi
  std::vector<std::unique_ptr<UIComponent>> *v110; // rbx
  UIResolvedDef *v111; // r15
  RenderableComponent *v112; // rdi
  unsigned __int8 v113; // r14
  unsigned __int8 v114; // al
  RenderableComponent **v115; // rcx
  RenderableComponent **v116; // r8
  UIControl *v117; // rdi
  UIResolvedDef *v118; // rdi
  __int64 v119; // rdx
  UIControl *v120; // rsi
  unsigned __int64 v121; // rdi
  unsigned __int64 v122; // rax
  unsigned __int64 v123; // rcx
  unsigned __int64 v124; // rsi
  std::vector<std::unique_ptr<UIComponent>> *v125; // rbx
  RuinedPortalFeature *v126; // r14
  RenderableComponent *v127; // rdi
  unsigned __int8 v128; // r14
  unsigned __int8 v129; // al
  RenderableComponent **v130; // rcx
  RenderableComponent **v131; // r8
  UIControl *v132; // rdi
  UIControl *v133; // rsi
  __int64 v134; // rdx
  char *v135; // rsi
  std::unique_ptr<StructureFeature> *v136; // r15
  __int64 v137; // rdi
  StructureFeature *v138; // rax
  unsigned __int64 v139; // rdx
  unsigned __int64 v140; // r14
  std::unique_ptr<StructureFeature> *v141; // rbx
  RenderableComponent *v142; // rdi
  unsigned __int8 v143; // r15
  unsigned __int8 v144; // al
  RenderableComponent **v145; // rcx
  RenderableComponent **v146; // r8
  UIControl *v147; // rdi
  UIResolvedDef *v148; // rsi
  __int64 v149; // rdx
  UIResolvedDef *v150; // r13
  char *v151; // rsi
  std::unique_ptr<StructureFeature> *v152; // rbx
  __int64 v153; // rdi
  StructureFeature *Myval2; // rax
  unsigned __int64 v155; // rdx
  unsigned __int64 v156; // r14
  std::unique_ptr<StructureFeature> *v157; // r12
  RenderableComponent *v158; // rdi
  unsigned __int8 v159; // bl
  unsigned __int8 v160; // al
  RenderableComponent **Myfirst; // rcx
  RenderableComponent **Mylast; // r8
  UIControl *v163; // rdi
  __int64 v164; // rdx
  char *v165; // rsi
  std::unique_ptr<StructureFeature> *v166; // r15
  unsigned __int64 v167; // rdi
  StructureFeature *v168; // rax
  unsigned __int64 v169; // r8
  unsigned __int64 v170; // r14
  std::unique_ptr<StructureFeature> *v171; // rbx
  RenderableComponent *v172; // rdi
  unsigned __int8 v173; // r15
  unsigned __int8 v174; // al
  RenderableComponent **v175; // rcx
  RenderableComponent **v176; // r8
  UIControl *v177; // rdi
  UIControl *v178; // rsi
  __int64 v179; // rdx
  RenderableComponent *v180; // rsi
  std::unique_ptr<StructureFeature> *v181; // r13
  __int64 v182; // rdi
  StructureFeature *v183; // rax
  unsigned __int64 v184; // rdx
  unsigned __int64 v185; // r14
  std::unique_ptr<StructureFeature> *v186; // rbx
  RenderableComponent *v187; // rdi
  unsigned __int8 v188; // r13
  unsigned __int8 v189; // al
  RenderableComponent **v190; // rcx
  RenderableComponent **v191; // r8
  UIControl *v192; // rdi
  UIControl *v193; // rdi
  UIControl *v194; // rsi
  __int64 v195; // rdx
  RenderableComponent *v196; // rsi
  std::unique_ptr<StructureFeature> *v197; // r15
  __int64 v198; // rdi
  StructureFeature *v199; // rax
  unsigned __int64 v200; // rdx
  unsigned __int64 v201; // r14
  std::unique_ptr<StructureFeature> *v202; // rbx
  RenderableComponent *v203; // rdi
  unsigned __int8 v204; // r15
  unsigned __int8 v205; // al
  RenderableComponent **v206; // rcx
  RenderableComponent **v207; // r8
  UIControl *v208; // rdi
  __int64 v209; // rdx
  RenderableComponent *v210; // rsi
  std::unique_ptr<StructureFeature> *v211; // r15
  __int64 v212; // rdi
  StructureFeature *v213; // rax
  unsigned __int64 v214; // r8
  unsigned __int64 v215; // r14
  std::unique_ptr<StructureFeature> *v216; // rbx
  RenderableComponent *v217; // rdi
  unsigned __int8 v218; // r15
  unsigned __int8 v219; // al
  RenderableComponent **v220; // rcx
  RenderableComponent **v221; // r8
  UIControl *v222; // rdi
  UIResolvedDef *v223; // rdi
  UIControl *v224; // rsi
  __int64 v225; // rdx
  RenderableComponent *v226; // rsi
  std::unique_ptr<StructureFeature> *v227; // r15
  unsigned __int64 v228; // rdi
  StructureFeature *v229; // rax
  unsigned __int64 v230; // rdx
  unsigned __int64 v231; // r14
  std::unique_ptr<StructureFeature> *v232; // rbx
  RenderableComponent *v233; // rdi
  unsigned __int8 v234; // r15
  unsigned __int8 v235; // al
  RenderableComponent **v236; // rcx
  RenderableComponent **v237; // r8
  UIControl *v238; // rdi
  UIControl *v239; // rdi
  UIControl *v240; // rdi
  __int64 v241; // rdx
  char *v242; // rsi
  std::unique_ptr<StructureFeature> *v243; // r15
  __int64 v244; // rdi
  StructureFeature *v245; // rax
  unsigned __int64 v246; // rdx
  unsigned __int64 v247; // r14
  std::unique_ptr<StructureFeature> *v248; // rbx
  RenderableComponent *v249; // rdi
  unsigned __int8 v250; // r15
  unsigned __int8 v251; // al
  RenderableComponent **v252; // rcx
  RenderableComponent **v253; // r8
  UIControl *v254; // rdi
  UIControl *v255; // rdi
  UIControl *v256; // rsi
  __int64 v257; // rdx
  char *v258; // rsi
  unsigned __int64 v259; // rdi
  unsigned __int64 v260; // rax
  unsigned __int64 v261; // rcx
  unsigned __int64 v262; // rsi
  std::vector<std::unique_ptr<UIComponent>> *v263; // rbx
  UIResolvedDef *v264; // r14
  RenderableComponent *v265; // rdi
  unsigned __int8 v266; // r14
  unsigned __int8 v267; // al
  RenderableComponent **v268; // rcx
  RenderableComponent **v269; // r8
  signed __int64 v270; // rsi
  const std::string *v271; // rdi
  _QWORD *v272; // rbx
  unsigned __int64 v273; // rbx
  void *v274; // rax
  _QWORD *v275; // rcx
  std::unique_ptr<RuinedPortalFeature> *v276; // rsi
  std::unique_ptr<UIComponent> *v277; // rax
  std::unique_ptr<RuinedPortalFeature> *v278; // rbx
  UIComponent *v279; // rcx
  RuinedPortalFeature *v280; // rax
  RuinedPortalFeature *v281; // rcx
  std::unique_ptr<RuinedPortalFeature> *v282; // r14
  StructureFeature *v283; // rax
  std::unique_ptr<RuinedPortalFeature> *p_mActiveBlueprintCreateCount; // rbx
  StructureFeature_vtbl *v285; // rcx
  RuinedPortalFeature *v286; // rax
  RuinedPortalFeature *v287; // rcx
  std::unique_ptr<RuinedPortalFeature> *v288; // r14
  StructureFeature *v289; // rax
  std::unique_ptr<RuinedPortalFeature> *v290; // rbx
  StructureFeature_vtbl *v291; // rcx
  RuinedPortalFeature *v292; // rax
  RuinedPortalFeature *v293; // rcx
  std::unique_ptr<RuinedPortalFeature> *v294; // r14
  StructureFeature *v295; // rax
  std::unique_ptr<RuinedPortalFeature> *v296; // rbx
  StructureFeature_vtbl *v297; // rcx
  RuinedPortalFeature *v298; // rax
  RuinedPortalFeature *v299; // rcx
  std::unique_ptr<RuinedPortalFeature> *v300; // r14
  StructureFeature *v301; // rax
  std::unique_ptr<RuinedPortalFeature> *v302; // rbx
  StructureFeature_vtbl *v303; // rcx
  RuinedPortalFeature *v304; // rax
  RuinedPortalFeature *v305; // rcx
  std::unique_ptr<RuinedPortalFeature> *v306; // r14
  StructureFeature *v307; // rax
  std::unique_ptr<RuinedPortalFeature> *v308; // rbx
  StructureFeature_vtbl *v309; // rcx
  RuinedPortalFeature *v310; // rax
  RuinedPortalFeature *v311; // rcx
  std::unique_ptr<RuinedPortalFeature> *v312; // r14
  StructureFeature *v313; // rax
  std::unique_ptr<RuinedPortalFeature> *v314; // rbx
  StructureFeature_vtbl *v315; // rcx
  RuinedPortalFeature *v316; // rax
  RuinedPortalFeature *v317; // rcx
  std::unique_ptr<RuinedPortalFeature> *v318; // rsi
  std::unique_ptr<UIComponent> *v319; // rax
  std::unique_ptr<RuinedPortalFeature> *v320; // rbx
  UIComponent *v321; // rcx
  RuinedPortalFeature *v322; // rax
  RuinedPortalFeature *v323; // rcx
  std::unique_ptr<RuinedPortalFeature> *v324; // rsi
  std::unique_ptr<UIComponent> *v325; // rax
  std::unique_ptr<RuinedPortalFeature> *v326; // rbx
  UIComponent *v327; // rcx
  RuinedPortalFeature *v328; // rax
  RuinedPortalFeature *v329; // rcx
  std::unique_ptr<RuinedPortalFeature> *v330; // r14
  StructureFeature *v331; // rax
  std::unique_ptr<RuinedPortalFeature> *v332; // rbx
  StructureFeature_vtbl *v333; // rcx
  RuinedPortalFeature *v334; // rax
  RuinedPortalFeature *v335; // rcx
  std::unique_ptr<RuinedPortalFeature> *v336; // r14
  StructureFeature *v337; // rax
  std::unique_ptr<RuinedPortalFeature> *v338; // rbx
  StructureFeature_vtbl *v339; // rcx
  RuinedPortalFeature *v340; // rax
  RuinedPortalFeature *v341; // rcx
  std::unique_ptr<RuinedPortalFeature> *v342; // rsi
  std::unique_ptr<UIComponent> *v343; // rax
  std::unique_ptr<RuinedPortalFeature> *v344; // rbx
  UIComponent *v345; // rcx
  RuinedPortalFeature *v346; // rax
  RuinedPortalFeature *v347; // rcx
  std::unique_ptr<RuinedPortalFeature> *v348; // r14
  StructureFeature *v349; // rax
  std::unique_ptr<RuinedPortalFeature> *v350; // rbx
  StructureFeature_vtbl *v351; // rcx
  RuinedPortalFeature *v352; // rax
  RuinedPortalFeature *v353; // rcx
  std::unique_ptr<RuinedPortalFeature> *v354; // r14
  StructureFeature *v355; // rax
  std::unique_ptr<RuinedPortalFeature> *v356; // rbx
  StructureFeature_vtbl *v357; // rcx
  RuinedPortalFeature *v358; // rax
  RuinedPortalFeature *v359; // rcx
  std::unique_ptr<RuinedPortalFeature> *v360; // rsi
  std::unique_ptr<UIComponent> *v361; // rax
  std::unique_ptr<RuinedPortalFeature> *v362; // rbx
  UIComponent *v363; // rcx
  RuinedPortalFeature *v364; // rax
  RuinedPortalFeature *v365; // rcx
  Json::Value *v366; // rax
  UIResolvedDef *v367; // rdi
  void *v368; // rcx
  unsigned __int64 v369; // rdx
  UIResolvedDef *v370; // rax
  UIResolvedDef *v371; // rax
  void *v372; // rcx
  unsigned __int64 v373; // rdx
  void *v374; // rcx
  unsigned __int64 v375; // rdx
  volatile signed __int32 *v376; // rsi
  RuinedPortalFeature *v377; // rcx
  RuinedPortalFeature *v378; // rcx
  RuinedPortalFeature *v379; // rcx
  RuinedPortalFeature *v380; // rcx
  RuinedPortalFeature *v381; // rcx
  RuinedPortalFeature *v382; // rcx
  RuinedPortalFeature *v383; // rcx
  RuinedPortalFeature *v384; // rcx
  RuinedPortalFeature *v385; // rcx
  RuinedPortalFeature *v386; // rcx
  RuinedPortalFeature *v387; // rcx
  RuinedPortalFeature *v388; // rcx
  RuinedPortalFeature *v389; // rcx
  RuinedPortalFeature *v390; // rcx
  RuinedPortalFeature *v391; // rcx
  unsigned __int8 v392; // r14
  CustomFrameUpdateComponent **v393; // rcx
  CustomFrameUpdateComponent **v394; // r8
  UIComponent *v395; // rcx
  unsigned __int8 v396; // bl
  CustomFrameUpdateComponent **v397; // rcx
  CustomFrameUpdateComponent **v398; // r8
  void (__fastcall ***v399)(_QWORD, __int64); // rcx
  unsigned __int8 v400; // r15
  CustomFrameUpdateComponent **v401; // rcx
  CustomFrameUpdateComponent **v402; // r8
  void (__fastcall ***v403)(_QWORD, __int64); // rcx
  unsigned __int8 v404; // r15
  CustomFrameUpdateComponent **v405; // rcx
  CustomFrameUpdateComponent **v406; // r8
  void (__fastcall ***v407)(_QWORD, __int64); // rcx
  unsigned __int8 v408; // r15
  CustomFrameUpdateComponent **v409; // rcx
  CustomFrameUpdateComponent **v410; // r8
  void (__fastcall ***v411)(_QWORD, __int64); // rcx
  unsigned __int8 v412; // r15
  CustomFrameUpdateComponent **v413; // rcx
  CustomFrameUpdateComponent **v414; // r8
  void (__fastcall ***v415)(_QWORD, __int64); // rcx
  unsigned __int8 v416; // r15
  CustomFrameUpdateComponent **v417; // rcx
  CustomFrameUpdateComponent **v418; // r8
  void (__fastcall ***v419)(_QWORD, __int64); // rcx
  unsigned __int8 v420; // r14
  CustomFrameUpdateComponent **v421; // rcx
  CustomFrameUpdateComponent **v422; // r8
  UIComponent *v423; // rcx
  unsigned __int8 v424; // r14
  CustomFrameUpdateComponent **v425; // rcx
  CustomFrameUpdateComponent **v426; // r8
  UIComponent *v427; // rcx
  unsigned __int8 v428; // r15
  CustomFrameUpdateComponent **v429; // rcx
  CustomFrameUpdateComponent **v430; // r8
  void (__fastcall ***v431)(_QWORD, __int64); // rcx
  unsigned __int8 v432; // r13
  CustomFrameUpdateComponent **v433; // rcx
  CustomFrameUpdateComponent **v434; // r8
  void (__fastcall ***v435)(_QWORD, __int64); // rcx
  unsigned __int8 v436; // r14
  CustomFrameUpdateComponent **v437; // rcx
  CustomFrameUpdateComponent **v438; // r8
  UIComponent *v439; // rcx
  unsigned __int8 v440; // r15
  CustomFrameUpdateComponent **v441; // rcx
  CustomFrameUpdateComponent **v442; // r8
  void (__fastcall ***v443)(_QWORD, __int64); // rcx
  unsigned __int8 v444; // r15
  CustomFrameUpdateComponent **v445; // rcx
  CustomFrameUpdateComponent **v446; // r8
  void (__fastcall ***v447)(_QWORD, __int64); // rcx
  unsigned __int8 v448; // r14
  CustomFrameUpdateComponent **v449; // rcx
  CustomFrameUpdateComponent **v450; // r8
  UIComponent *v451; // rcx
  UIControl *v452; // rax
  RenderableComponent **v453; // rdx
  UIControl *v454; // rax
  CustomFrameUpdateComponent **v455; // rdx
  unsigned __int64 v456; // rax
  unsigned __int64 v457; // rax
  unsigned __int64 v458; // rcx
  std::unique_ptr<UIComponent> *v459; // rax
  Json::Value *v460; // rsi
  bool v461; // cl
  bool v462; // al
  Json::Value *v463; // rsi
  bool v464; // cl
  int v465; // eax
  Json::Value *v466; // rsi
  bool isNumeric; // al
  __m128i v468; // xmm0
  Json::Value *v469; // rsi
  __m128i v470; // xmm0
  Json::Value *v471; // rsi
  unsigned __int64 *p_Mysize; // rsi
  __int64 v474; // rdx
  Json::Value *v475; // r15
  void *v476; // rcx
  unsigned __int64 v477; // rdx
  __int64 v478; // rdx
  unsigned __int8 *v479; // rsi
  unsigned __int64 v480; // rax
  _QWORD *v481; // rcx
  int v482; // r9d
  unsigned __int64 v483; // r8
  __int64 v484; // r8
  unsigned __int64 v485; // rdx
  unsigned __int8 *v486; // rsi
  unsigned __int64 v487; // rax
  _QWORD *v488; // rcx
  int v489; // r9d
  unsigned __int64 v490; // r8
  __int64 v491; // r8
  unsigned __int64 v492; // rdx
  unsigned __int8 *v493; // rsi
  unsigned __int64 v494; // rax
  _QWORD *v495; // rcx
  int v496; // r9d
  unsigned __int64 v497; // r8
  __int64 v498; // r8
  unsigned __int64 v499; // rdx
  unsigned __int8 *v500; // rsi
  unsigned __int64 v501; // rax
  _QWORD *v502; // rcx
  int v503; // r9d
  unsigned __int64 v504; // r8
  __int64 v505; // r8
  unsigned __int64 v506; // rdx
  unsigned __int8 *v507; // rsi
  unsigned __int64 v508; // rax
  _QWORD *v509; // rcx
  int v510; // r9d
  unsigned __int64 v511; // r8
  __int64 v512; // r8
  unsigned __int64 v513; // rdx
  Json::Value *v514; // rsi
  bool isUInt; // cl
  unsigned int v516; // eax
  __int64 v517; // rdx
  UIControl *v518; // rdi
  UIControl *v519; // rax
  RenderableComponent **v520; // rdx
  UIControl *v521; // rax
  CustomFrameUpdateComponent **v522; // rdx
  unsigned __int64 mComponentsInUse; // rax
  Core::PathBuffer<std::string > *p_mPath; // r14
  unsigned __int64 v525; // rax
  unsigned __int64 v526; // rcx
  std::unique_ptr<UIComponent> *v527; // rax
  CustomRenderComponent *v528; // r12
  __m128i *v529; // rsi
  Json::Value *Value; // rax
  Json::Value *v531; // rax
  volatile signed __int32 *Rep; // rdi
  std::_Ref_count_base *v533; // rsi
  volatile signed __int32 *p_Uses; // rbx
  UICustomRenderer *v535; // rax
  __m128i *v536; // rdi
  __m128i *v537; // rdi
  __m128i *v538; // rsi
  char *v539; // rax
  UIControl *v540; // rax
  RenderableComponent **v541; // rdx
  UIControl *v542; // rax
  CustomFrameUpdateComponent **v543; // rdx
  void *v544; // rcx
  unsigned __int64 v545; // rdx
  void *v546; // rcx
  unsigned __int64 v547; // rdx
  char *v548; // rcx
  unsigned __int64 v549; // rdx
  char *v550; // rcx
  unsigned __int64 v551; // rdx
  UIControl *v552; // rax
  RenderableComponent **v553; // rdx
  UIControl *v554; // rax
  CustomFrameUpdateComponent **v555; // rdx
  unsigned __int64 v556; // rax
  unsigned __int64 v557; // rax
  unsigned __int64 v558; // rcx
  std::unique_ptr<UIComponent> *v559; // rax
  UIComponent *v560; // r15
  std::string *v561; // rsi
  int v562; // edx
  unsigned __int64 v563; // rcx
  __int64 v564; // rcx
  std::string *v565; // rsi
  int v566; // edx
  unsigned __int64 v567; // rcx
  __int64 v568; // rcx
  std::string *v569; // rsi
  int v570; // edx
  unsigned __int64 v571; // rcx
  __int64 v572; // rcx
  std::string *v573; // rsi
  int v574; // edx
  unsigned __int64 v575; // rcx
  __int64 v576; // rcx
  std::string *v577; // rsi
  int v578; // edx
  unsigned __int64 v579; // rcx
  __int64 v580; // rcx
  Json::Value *v581; // rsi
  bool v582; // cl
  int v583; // eax
  Json::Value *v584; // rsi
  bool v585; // al
  Json::Value *v586; // rsi
  __m128i v587; // xmm0
  webrtc::internal::RaceCheckerScope *v588; // rax
  __m128i v589; // xmm6
  Json::Value *v590; // rsi
  __m128i v591; // xmm0
  UIResolvedDef *v592; // rsi
  std::string::assign::<lambda_1> v593; // r8
  UIComponent_vtbl *v594; // rdi
  size_t v595; // rbx
  unsigned __int64 v596; // rax
  void *v597; // rcx
  unsigned __int64 v598; // rdx
  UIResolvedDef *v599; // rsi
  std::string::assign::<lambda_1> v600; // r8
  UIControl *v601; // rdi
  size_t v602; // rbx
  unsigned __int64 v603; // rax
  void *v604; // rcx
  unsigned __int64 v605; // rdx
  std::string *v606; // rsi
  int v607; // edx
  unsigned __int64 v608; // rcx
  __int64 v609; // rcx
  Json::Value *v610; // rsi
  char v611; // al
  void *v612; // rcx
  unsigned __int64 v613; // rdx
  void *v614; // rcx
  unsigned __int64 v615; // rdx
  char *v616; // rcx
  unsigned __int64 v617; // rdx
  char *v618; // rcx
  unsigned __int64 v619; // rdx
  char *v620; // rcx
  unsigned __int64 v621; // rdx
  char *v622; // rcx
  unsigned __int64 v623; // rdx
  char *v624; // rcx
  unsigned __int64 v625; // rdx
  char *v626; // rcx
  unsigned __int64 v627; // rdx
  char *v628; // rcx
  unsigned __int64 v629; // rdx
  char *v630; // rcx
  unsigned __int64 v631; // rdx
  char *v632; // rcx
  unsigned __int64 v633; // rdx
  char *v634; // rcx
  unsigned __int64 v635; // rdx
  char *v636; // rcx
  unsigned __int64 v637; // rdx
  UIControl *v638; // rdi
  UIControl *v639; // rax
  RenderableComponent **v640; // rdx
  UIControl *v641; // rax
  CustomFrameUpdateComponent **v642; // rdx
  unsigned __int64 v643; // rax
  unsigned __int64 v644; // rax
  unsigned __int64 v645; // rcx
  std::unique_ptr<UIComponent> *v646; // rax
  UIComponent *v647; // rdi
  Json::Value *v648; // rsi
  bool v649; // al
  Json::Value *v650; // rsi
  char v651; // al
  Json::Value *v652; // rsi
  char v653; // al
  Json::Value *v654; // rsi
  char v655; // al
  Json::Value *v656; // rsi
  char v657; // al
  Json::Value *v658; // rsi
  char v659; // al
  Json::Value *v660; // rsi
  char v661; // al
  Json::Value *v662; // rsi
  char v663; // al
  Json::Value *v664; // rsi
  char v665; // al
  Json::Value *v666; // rsi
  bool v667; // al
  Json::Value *v668; // rsi
  char v669; // al
  Json::Value *v670; // rsi
  char v671; // al
  Json::Value *v672; // rsi
  char v673; // al
  Json::Value *v674; // rsi
  char v675; // al
  Json::Value *v676; // rsi
  char v677; // al
  Json::Value *v678; // rsi
  char v679; // al
  Json::Value *v680; // rsi
  __m128i v681; // xmm0
  Json::Value *v682; // rsi
  bool v683; // al
  Json::Value *v684; // rsi
  char v685; // al
  Json::Value *v686; // rsi
  char v687; // al
  UIControl *v688; // rax
  RenderableComponent **v689; // rdx
  UIControl *v690; // rax
  CustomFrameUpdateComponent **v691; // rdx
  UIControl *v692; // rax
  RenderableComponent **v693; // rdx
  ui::OrientationType v694; // r8d
  UIControl *v695; // rax
  CustomFrameUpdateComponent **v696; // rdx
  unsigned __int64 v697; // rax
  unsigned __int64 v698; // rax
  unsigned __int64 v699; // rcx
  std::unique_ptr<UIComponent> *v700; // rax
  UIComponent *v701; // rdi
  Json::Value *v702; // rsi
  bool v703; // al
  Json::Value *v704; // rsi
  bool v705; // al
  UIControl *v706; // rax
  RenderableComponent **v707; // rdx
  UIControl *v708; // rax
  CustomFrameUpdateComponent **v709; // rdx
  unsigned __int64 v710; // rax
  unsigned __int64 v711; // rax
  unsigned __int64 v712; // rcx
  std::unique_ptr<UIComponent> *v713; // rax
  UIComponent *v714; // rdi
  std::string *v715; // r15
  std::string *p_formal; // r14
  char *v717; // rsi
  char *v718; // rsi
  char *v719; // rsi
  std::string *v720; // rax
  int v721; // r8d
  unsigned __int64 v722; // rdx
  __int64 v723; // rdx
  std::string *v724; // rax
  int v725; // r8d
  unsigned __int64 v726; // rdx
  __int64 v727; // rdx
  int v728; // edx
  unsigned __int64 v729; // rcx
  __int64 v730; // rcx
  int v731; // edx
  unsigned __int64 v732; // rcx
  __int64 v733; // rcx
  std::string *v734; // rax
  int v735; // r8d
  unsigned __int64 v736; // rdx
  __int64 v737; // rdx
  Json::Value *v738; // rsi
  __m128i v739; // xmm0
  Json::Value *v740; // rsi
  bool v741; // al
  Json::Value *v742; // rsi
  bool v743; // al
  Json::Value *v744; // rsi
  bool v745; // al
  Json::Value *v746; // rsi
  bool v747; // cl
  bool v748; // al
  Json::Value *v749; // rsi
  bool v750; // al
  void *v751; // rcx
  unsigned __int64 v752; // rdx
  void *v753; // rcx
  unsigned __int64 v754; // rdx
  char *v755; // rcx
  unsigned __int64 v756; // rdx
  char *v757; // rcx
  unsigned __int64 v758; // rdx
  char *v759; // rcx
  unsigned __int64 v760; // rdx
  Json::Value *v761; // rsi
  bool v762; // al
  char *v763; // rcx
  unsigned __int64 v764; // rdx
  char *v765; // rcx
  unsigned __int64 v766; // rdx
  char *v767; // rcx
  unsigned __int64 v768; // rdx
  char *v769; // rcx
  unsigned __int64 v770; // rdx
  char *v771; // rcx
  unsigned __int64 v772; // rdx
  UIControl *v773; // rax
  RenderableComponent **v774; // rdx
  UIControl *v775; // rax
  CustomFrameUpdateComponent **v776; // rdx
  UIControl *v777; // rax
  RenderableComponent **v778; // rdx
  UIControl *v779; // rax
  CustomFrameUpdateComponent **v780; // rdx
  void *v781; // rcx
  unsigned __int64 v782; // rdx
  unsigned __int64 v783; // rax
  unsigned __int64 v784; // rax
  unsigned __int64 v785; // rcx
  std::unique_ptr<UIComponent> *v786; // rax
  UIComponent *v787; // r15
  UIResolvedDef *v788; // rsi
  std::string::assign::<lambda_1> v789; // r8
  UIControl *v790; // rdi
  size_t v791; // rbx
  unsigned __int64 v792; // rax
  void *v793; // rcx
  unsigned __int64 v794; // rdx
  UIResolvedDef *v795; // rsi
  std::string::assign::<lambda_1> v796; // r8
  UIControl *v797; // rdi
  size_t v798; // rbx
  unsigned __int64 v799; // rax
  void *v800; // rcx
  unsigned __int64 v801; // rdx
  UIControl *v802; // rax
  RenderableComponent **v803; // rdx
  UIControl *v804; // rax
  CustomFrameUpdateComponent **v805; // rdx
  unsigned __int64 v806; // rax
  unsigned __int64 v807; // rax
  unsigned __int64 v808; // rcx
  std::unique_ptr<UIComponent> *v809; // rax
  Json::Value *v810; // rsi
  unsigned __int64 v811; // rdx
  char *v812; // rcx
  __int64 v814; // rdx
  Json::Value *v815; // rdi
  std::string *v816; // rsi
  ResourceFileSystem v817; // edi
  unsigned __int64 v818; // rsi
  std::string *v819; // r15
  size_t v820; // r14
  unsigned __int64 v821; // rax
  __int64 v822; // rdi
  unsigned __int64 v823; // r13
  unsigned __int64 v824; // rsi
  void *(__fastcall *allocate)(Bedrock::Memory::IMemoryAllocator *, unsigned __int64); // rax
  __int64 v826; // r15
  _QWORD *v827; // rax
  char *v828; // rcx
  unsigned __int64 v829; // rdx
  char *v830; // rcx
  unsigned __int64 v831; // rdx
  __int64 v832; // rdx
  UIComponent *v833; // r8
  char *v834; // rcx
  UIControl *v835; // rax
  UIControl *v836; // rax
  RenderableComponent **v837; // rdx
  UIControl *v838; // rax
  CustomFrameUpdateComponent **v839; // rdx
  unsigned __int64 v840; // rcx
  unsigned __int64 v841; // rax
  unsigned __int64 v842; // rax
  std::unique_ptr<UIComponent> *v843; // rax
  UIComponent *v844; // r14
  unsigned __int64 v845; // rdi
  __int64 v846; // rax
  _BYTE *v847; // rax
  volatile signed __int32 *v848; // rsi
  char *v849; // rsi
  __int64 v850; // rax
  unsigned __int64 v851; // rax
  __int64 v852; // rax
  unsigned __int64 v853; // rax
  volatile signed __int32 *v854; // rsi
  unsigned __int64 v855; // rax
  volatile signed __int32 *v856; // rsi
  unsigned __int64 v857; // rax
  volatile signed __int32 *mOwner; // rsi
  volatile signed __int32 *v859; // rsi
  volatile signed __int32 *v860; // rsi
  std::string *v861; // rsi
  int v862; // edx
  unsigned __int64 v863; // rcx
  __int64 v864; // rcx
  UIResolvedDef *v865; // rsi
  std::string::assign::<lambda_1> v866; // r8
  UIControl *v867; // rdi
  size_t v868; // rbx
  unsigned __int64 v869; // rax
  void *v870; // rcx
  unsigned __int64 v871; // rdx
  Json::Value *v872; // rsi
  bool v873; // al
  Json::Value *v874; // rsi
  bool v875; // al
  std::string *v876; // rsi
  int v877; // eax
  Json::Value *v878; // rsi
  bool isInt; // cl
  int v880; // eax
  void *v881; // rcx
  unsigned __int64 v882; // rdx
  char *v883; // rcx
  unsigned __int64 v884; // rdx
  char *v885; // rcx
  unsigned __int64 v886; // rdx
  Json::Value *v887; // rsi
  bool isIntegral; // cl
  bool v889; // al
  Json::Value *v890; // rsi
  bool v891; // al
  UIControl *v892; // rax
  char *v893; // rcx
  unsigned __int64 v894; // rdx
  char *v895; // rcx
  unsigned __int64 v896; // rdx
  UIControl *v897; // rax
  RenderableComponent **v898; // rdx
  UIControl *v899; // rax
  CustomFrameUpdateComponent **v900; // rdx
  unsigned __int64 v901; // rax
  unsigned __int64 v902; // rax
  unsigned __int64 v903; // rcx
  std::unique_ptr<UIComponent> *v904; // rax
  UIComponent *v905; // rbx
  unsigned __int8 *v906; // rsi
  int v907; // edx
  unsigned __int64 v908; // rcx
  __int64 v909; // rcx
  void *v910; // rcx
  unsigned __int64 v911; // rdx
  char *v912; // rcx
  unsigned __int64 v913; // rdx
  void *v914; // rcx
  unsigned __int64 v915; // rdx
  UIControl *v916; // rax
  RenderableComponent **v917; // rdx
  UIControl *v918; // rax
  CustomFrameUpdateComponent **v919; // rdx
  unsigned __int64 v920; // rax
  unsigned __int64 v921; // rax
  unsigned __int64 v922; // rcx
  std::unique_ptr<UIComponent> *v923; // rax
  std::vector<ScriptModuleMinecraft::ScriptItemFilterError> *v924; // rdi
  ScriptModuleMinecraft::ScriptItemFilterError *v925; // rax
  char *Buf; // rcx
  UIControl *v928; // rax
  RenderableComponent **v929; // rdx
  UIControl *v930; // rax
  CustomFrameUpdateComponent **v931; // rdx
  unsigned __int64 v932; // rax
  unsigned __int64 v933; // rax
  unsigned __int64 v934; // rcx
  std::unique_ptr<UIComponent> *v935; // rax
  UIComponent *v936; // r15
  std::string *v937; // rsi
  int v938; // edx
  unsigned __int64 v939; // rcx
  __int64 v940; // rcx
  UIResolvedDef *v941; // rsi
  std::string::assign::<lambda_1> v942; // r8
  UIControl *v943; // rdi
  size_t v944; // rbx
  unsigned __int64 v945; // rax
  void *v946; // rcx
  unsigned __int64 v947; // rdx
  void *v948; // rcx
  unsigned __int64 v949; // rdx
  void *v950; // rcx
  unsigned __int64 v951; // rdx
  char *v952; // rcx
  unsigned __int64 v953; // rdx
  char *v954; // rcx
  unsigned __int64 v955; // rdx
  void **v956; // rcx
  UIComponent *v957; // rbx
  UIComponent *v958; // rdx
  volatile signed __int32 *v959; // rdi
  UICustomRenderer *v960; // rax
  volatile signed __int32 *v961; // rsi
  volatile signed __int32 *v962; // rdi
  void *v963; // rcx
  unsigned __int64 v964; // rdx
  __int64 v965; // rdx
  UIResolvedDef *v966; // rsi
  unsigned __int64 v967; // rax
  std::unique_ptr<StructureFeature> *v968; // r15
  RenderableComponent *v969; // rsi
  UIControl *v970; // rbx
  unsigned __int64 mBitId; // rdi
  unsigned __int64 v972; // rcx
  unsigned __int64 v973; // rdx
  unsigned __int64 v974; // r14
  RenderableComponent *v975; // rdi
  unsigned __int8 v976; // bl
  unsigned __int8 v977; // al
  RenderableComponent **v978; // rcx
  RenderableComponent **v979; // r8
  std::unique_ptr<RuinedPortalFeature> *v980; // r14
  std::unique_ptr<UIComponent> *v981; // rax
  std::unique_ptr<RuinedPortalFeature> *v982; // rbx
  UIComponent *v983; // rcx
  RuinedPortalFeature *v984; // rax
  RuinedPortalFeature *v985; // rcx
  char *v986; // rcx
  unsigned __int8 v987; // bl
  CustomFrameUpdateComponent **v988; // rcx
  CustomFrameUpdateComponent **v989; // r8
  void (__fastcall ***v990)(_QWORD, __int64); // rcx
  UIControl *v991; // rax
  RenderableComponent **v992; // rdx
  UIControl *v993; // rax
  CustomFrameUpdateComponent **v994; // rdx
  void *v995; // rcx
  unsigned __int64 v996; // rdx
  UIControl *v997; // rdi
  _QWORD *v998; // rsi
  PaperDollRenderer *v999; // rsi
  volatile signed __int32 *p_mOwner; // rdi
  volatile signed __int32 *v1001; // rsi
  __m128i *v1002; // rsi
  __int64 v1003; // rax
  __m128i *v1004; // rsi
  __int64 v1005; // rax
  char *v1006; // rax
  UIResolvedDef *v1007; // rsi
  ContentLog::ContentLogScope v1008; // [rsp+30h] [rbp-50h] BYREF
  std::string_view v1009; // [rsp+48h] [rbp-38h] BYREF
  std::string_view v1010; // [rsp+58h] [rbp-28h] BYREF
  std::string_view v1011; // [rsp+68h] [rbp-18h] BYREF
  std::string_view v1012; // [rsp+78h] [rbp-8h] BYREF
  std::string_view v1013; // [rsp+88h] [rbp+8h] BYREF
  std::string_view v1014; // [rsp+98h] [rbp+18h] BYREF
  std::string_view v1015; // [rsp+A8h] [rbp+28h] BYREF
  std::string_view v1016; // [rsp+B8h] [rbp+38h] BYREF
  std::string_view v1017; // [rsp+C8h] [rbp+48h] BYREF
  std::string_view v1018; // [rsp+D8h] [rbp+58h] BYREF
  std::string_view v1019; // [rsp+E8h] [rbp+68h] BYREF
  std::string_view v1020; // [rsp+F8h] [rbp+78h] BYREF
  std::string_view v1021; // [rsp+108h] [rbp+88h] BYREF
  std::string_view v1022; // [rsp+118h] [rbp+98h] BYREF
  std::string_view v1023; // [rsp+128h] [rbp+A8h] BYREF
  std::string_view v1024; // [rsp+138h] [rbp+B8h] BYREF
  std::string_view v1025; // [rsp+148h] [rbp+C8h] BYREF
  std::string_view v1026; // [rsp+158h] [rbp+D8h] BYREF
  std::string_view v1027; // [rsp+168h] [rbp+E8h] BYREF
  std::string_view v1028; // [rsp+178h] [rbp+F8h] BYREF
  std::string_view v1029; // [rsp+188h] [rbp+108h] BYREF
  std::string_view v1030; // [rsp+198h] [rbp+118h] BYREF
  UIComponent *v1031; // [rsp+1A8h] [rbp+128h]
  std::shared_ptr<UIControl> v1032; // [rsp+1B0h] [rbp+130h] BYREF
  std::string_view v1033; // [rsp+1C0h] [rbp+140h] BYREF
  std::string_view v1034; // [rsp+1D0h] [rbp+150h] BYREF
  std::string_view v1035; // [rsp+1E0h] [rbp+160h] BYREF
  std::string_view v1036; // [rsp+1F0h] [rbp+170h] BYREF
  std::string_view v1037; // [rsp+200h] [rbp+180h] BYREF
  UIResolvedDef _Args[8]; // [rsp+210h] [rbp+190h] BYREF
  size_t v1039; // [rsp+610h] [rbp+590h]
  _QWORD *p_Pmtx; // [rsp+618h] [rbp+598h]
  std::string_view v1041; // [rsp+620h] [rbp+5A0h] BYREF
  std::string_view v1042; // [rsp+630h] [rbp+5B0h] BYREF
  std::string_view v1043; // [rsp+640h] [rbp+5C0h] BYREF
  std::string_view v1044; // [rsp+650h] [rbp+5D0h] BYREF
  std::string_view v1045; // [rsp+660h] [rbp+5E0h] BYREF
  std::string v1046; // [rsp+670h] [rbp+5F0h] BYREF
  UIControl *v1047[2]; // [rsp+690h] [rbp+610h]
  std::string v1048; // [rsp+6A0h] [rbp+620h] BYREF
  std::string v1049; // [rsp+6C0h] [rbp+640h] BYREF
  std::string __formal; // [rsp+6E0h] [rbp+660h] BYREF
  std::string *v1051; // [rsp+718h] [rbp+698h]
  UIResolvedDef *v1052; // [rsp+720h] [rbp+6A0h]
  char *v1053; // [rsp+728h] [rbp+6A8h]
  RenderableComponent *v1054; // [rsp+730h] [rbp+6B0h]
  RenderableComponent *v1055; // [rsp+738h] [rbp+6B8h]
  RuinedPortalFeature *v1056; // [rsp+740h] [rbp+6C0h]
  RenderableComponent *v1057; // [rsp+748h] [rbp+6C8h]
  char *v1058; // [rsp+750h] [rbp+6D0h]
  char *v1059; // [rsp+758h] [rbp+6D8h]
  UIResolvedDef *v1060; // [rsp+760h] [rbp+6E0h]
  UIResolvedDef *v1061; // [rsp+768h] [rbp+6E8h]
  RenderableComponent *v1062; // [rsp+770h] [rbp+6F0h]
  char *v1063; // [rsp+778h] [rbp+6F8h]
  RuinedPortalFeature *v1064; // [rsp+780h] [rbp+700h]
  char *v1065; // [rsp+788h] [rbp+708h]
  RenderableComponent *v1066; // [rsp+790h] [rbp+710h]
  char *v1067; // [rsp+798h] [rbp+718h]
  std::string v1068; // [rsp+7A0h] [rbp+720h] BYREF
  std::string v1069; // [rsp+7C0h] [rbp+740h] BYREF
  std::string *v1070; // [rsp+7F8h] [rbp+778h]
  std::string_view v1071; // [rsp+800h] [rbp+780h] BYREF
  std::string v1072; // [rsp+810h] [rbp+790h] BYREF
  std::string v1073; // [rsp+830h] [rbp+7B0h] BYREF
  std::string Src; // [rsp+850h] [rbp+7D0h] BYREF
  std::string *p_Src; // [rsp+888h] [rbp+808h]
  std::string v1076; // [rsp+890h] [rbp+810h] BYREF
  ResourceLocation defaultValue; // [rsp+8B0h] [rbp+830h] BYREF
  ResourceLocation *v1078; // [rsp+8E8h] [rbp+868h]
  UIResolvedDef v1079; // [rsp+8F0h] [rbp+870h] BYREF
  UIComponent *v1080; // [rsp+978h] [rbp+8F8h]
  char v1081; // [rsp+987h] [rbp+907h]
  char v1082; // [rsp+988h] [rbp+908h]
  char v1083; // [rsp+989h] [rbp+909h]
  char v1084; // [rsp+98Ah] [rbp+90Ah]
  char v1085; // [rsp+98Bh] [rbp+90Bh]
  char v1086; // [rsp+98Ch] [rbp+90Ch]
  char v1087; // [rsp+98Dh] [rbp+90Dh]
  char v1088; // [rsp+98Eh] [rbp+90Eh]
  char v1089; // [rsp+98Fh] [rbp+90Fh]
  char v1090; // [rsp+990h] [rbp+910h]
  char v1091; // [rsp+991h] [rbp+911h]
  char v1092; // [rsp+992h] [rbp+912h]
  char v1093; // [rsp+993h] [rbp+913h]
  char v1094; // [rsp+994h] [rbp+914h]
  char v1095; // [rsp+995h] [rbp+915h]
  char v1096; // [rsp+996h] [rbp+916h]
  char v1097; // [rsp+997h] [rbp+917h]
  char v1098; // [rsp+998h] [rbp+918h]
  char v1099; // [rsp+999h] [rbp+919h]
  char v1100; // [rsp+99Ah] [rbp+91Ah]
  char v1101; // [rsp+99Bh] [rbp+91Bh]
  char v1102; // [rsp+99Ch] [rbp+91Ch]
  char v1103; // [rsp+99Dh] [rbp+91Dh]
  char v1104; // [rsp+99Eh] [rbp+91Eh]
  char v1105; // [rsp+99Fh] [rbp+91Fh]
  std::string v1106; // [rsp+9A0h] [rbp+920h] BYREF
  std::string *v1107; // [rsp+9D8h] [rbp+958h]
  RuinedPortalFeature *v1108; // [rsp+9E8h] [rbp+968h]
  UIResolvedDef *def; // [rsp+9F0h] [rbp+970h]
  UIResolvedDef *v1110; // [rsp+9F8h] [rbp+978h]
  UIControl *ownerControl; // [rsp+A00h] [rbp+980h]
  __int64 v1112; // [rsp+A08h] [rbp+988h]

  v1112 = -2;
  v1110 = a4;
  v9 = context;
  def = result;
  *(_OWORD *)v1047 = 0;
  LOBYTE(context) = 23;
  LOBYTE(ownerControl) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                           this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                           a2: (Memory::MemoryCategory)context);
  p_Pmtx = &v9->mLock._Pmtx;
  v10 = (UIControl *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 344);
  if ( v10 == nullptr )
    `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x158u, alignment: 0);
  v10->_Wptr._Rep = (std::_Ref_count_base *)0x100000001LL;
  v10->_Wptr._Ptr = (UIControl *)off_14E8D6E00;
  *(_OWORD *)&v10->mCachedPosition.x = 0;
  v10->mName._Mypair._Myval2._Bx._Ptr = nullptr;
  v10->mName._Mypair._Myval2._Bx._Buf[8] = 109;
  v10->mName._Mypair._Myval2._Bx._Buf[9] = 6;
  *(_WORD *)&v10->mName._Mypair._Myval2._Bx._Alias[10] = 0;
  BYTE1(v10->mName._Mypair._Myval2._Myres) = 0;
  WORD1(v10->mName._Mypair._Myval2._Myres) = 0;
  HIDWORD(v10->mName._Mypair._Myval2._Myres) = 0;
  v10->mParentRelativePosition = (glm::vec<2,float,0>)9LL;
  v10->mSize = (glm::vec<2,float,0>)15LL;
  strcpy((char *)&v10->mName._Mypair._Myval2._Mysize, "Undefine");
  *(_OWORD *)&v10->mMinSize.x = 0;
  *(_OWORD *)&v10->mAlpha = 0;
  v10->mClipOffset.y = 1.0;
  *(_OWORD *)&v10->mClipChangeEventId = 0;
  *(_OWORD *)((char *)&v10->mPropertyBagToPropagateToChildren._Mypair._Myval2 + 4) = 0;
  *(_OWORD *)((char *)&v10->mParent._Rep + 4) = 0;
  *(_OWORD *)((char *)&v10->mChildren._Mypair._Myval2._Mylast + 4) = 0;
  *(_OWORD *)((char *)&v10->mComponentsInUse + 4) = 0;
  *(_OWORD *)((char *)&v10->mComponents._Mypair._Myval2._Mylast + 4) = 0;
  *(_OWORD *)((char *)&v10->mRenderableComponentLookup._Mypair._Myval2._Myfirst + 4) = 0;
  *(_OWORD *)((char *)&v10->mRenderableComponentLookup._Mypair._Myval2._Myend + 4) = 0;
  *(_OWORD *)((char *)&v10->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast + 4) = 0;
  *(_OWORD *)((char *)&v10->mControlResolvers._Mypair._Myval2._Myfirst + 4) = 0;
  *(_OWORD *)((char *)&v10->mControlResolvers._Mypair._Myval2._Myend + 4) = 0;
  *(_OWORD *)((char *)&v10->mPostCreateVector._Mypair._Myval2._Mylast + 4) = 0;
  *(_OWORD *)&v10->mControlScreenAction = 0;
  v10->mModalAncestor._Rep = a6;
  v10[1].std::enable_shared_from_this<UIControl> = 0;
  _InterlockedIncrement((volatile signed __int32 *)&v10->_Wptr._Rep);
  _InterlockedIncrement((volatile signed __int32 *)&v10->_Wptr._Rep + 1);
  v10->mCachedPosition = (glm::vec<2,float,0>)&v10->mCachedPosition;
  v11 = *((volatile signed __int32 **)v10 + 3);
  *((_QWORD *)v10 + 3) = v10;
  if ( v11 != nullptr && _InterlockedDecrement(v11 + 3) == 0 )
    (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v11 + 8LL))(a1: v11);
  if ( _InterlockedDecrement((volatile signed __int32 *)&v10->_Wptr._Rep) == 0 )
  {
    ((void (__fastcall *)(UIControl *))v10->_Wptr._Ptr->_Wptr._Ptr)(a1: v10);
    if ( _InterlockedDecrement((volatile signed __int32 *)&v10->_Wptr._Rep + 1) == 0 )
      ((void (__fastcall *)(UIControl *))v10->_Wptr._Ptr->_Wptr._Rep)(a1: v10);
  }
  v1047[0] = (UIControl *)&v10->mCachedPosition;
  v12 = (volatile signed __int32 *)v1047[1];
  v1047[1] = v10;
  if ( v12 != nullptr && _InterlockedDecrement(v12 + 2) == 0 )
  {
    (**(void (__fastcall ***)(volatile signed __int32 *))v12)(a1: v12);
    if ( _InterlockedDecrement(v12 + 3) == 0 )
      (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v12 + 8LL))(a1: v12);
  }
  Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
    this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
    a2: (Memory::MemoryCategory)ownerControl);
  if ( a8 != 0 )
    UIControl::setIsTemplate(this: v1047[0], a2: true);
  if ( a5 != nullptr )
  {
    v1032 = 0;
    if ( v1047[1] != nullptr )
    {
      _InterlockedIncrement((volatile signed __int32 *)&v1047[1]->_Wptr._Rep);
      v14 = (std::_Ref_count_base *)v1047[1];
    }
    else
    {
      v14 = nullptr;
    }
    ownerControl = v1047[0];
    v1032._Ptr = v1047[0];
    v1032._Rep = v14;
    UIControl::addChild(this: a5, child: &v1032, childInsertPosition: a7);
  }
  else
  {
    ownerControl = v1047[0];
  }
  _Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[5] = 0;
  *(_WORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[6] = 0;
  *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] = 12;
  _Args[0].mDefNamespace._Mypair._Myval2._Mysize = 15;
  strcpy((char *)&_Args[0].mIgnored, "{ui_control}");
  Mysize = v1110->mDefName._Mypair._Myval2._Mysize;
  if ( Mysize != 0 )
  {
    if ( v1110->mDefName._Mypair._Myval2._Myres < 0x10 )
      p_mDefName = &v1110->mDefName;
    else
      p_mDefName = (const std::string *)v1110->mDefName._Mypair._Myval2._Bx._Ptr;
    p_mName = &ownerControl->mName;
    Myres = ownerControl->mName._Mypair._Myval2._Myres;
    if ( Mysize <= Myres )
    {
      if ( Myres >= 0x10 )
        p_mName = (std::string *)ownerControl->mName._Mypair._Myval2._Bx._Ptr;
      ownerControl->mName._Mypair._Myval2._Mysize = Mysize;
      memmove_0(a1: p_mName, Src: p_mDefName, Size: Mysize);
      p_mName->_Mypair._Myval2._Bx._Buf[Mysize] = 0;
    }
    else
    {
      ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
        this: &ownerControl->mName,
        _New_size: v1110->mDefName._Mypair._Myval2._Mysize,
        _Fn: v13,
        _Args: p_mDefName->_Mypair._Myval2._Bx._Buf);
    }
  }
  else
  {
    Ptr = &ownerControl->mName;
    v18 = ownerControl->mName._Mypair._Myval2._Myres;
    if ( v18 >= 0xC )
    {
      if ( v18 >= 0x10 )
        Ptr = (std::string *)ownerControl->mName._Mypair._Myval2._Bx._Ptr;
      ownerControl->mName._Mypair._Myval2._Mysize = 12;
      v21 = *(char **)&_Args[0].mIgnored;
      *(_DWORD *)&Ptr->_Mypair._Myval2._Bx._Alias[8] = *(_DWORD *)_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf;
      Ptr->_Mypair._Myval2._Bx._Ptr = v21;
      Ptr->_Mypair._Myval2._Bx._Buf[12] = 0;
    }
    else
    {
      ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
        this: Ptr,
        _New_size: 0xCu,
        _Fn: v13,
        _Args: (const char *)&_Args[0].mIgnored);
    }
  }
  if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
  {
    v22 = *(void **)&_Args[0].mIgnored;
    v23 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
    if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
        goto LABEL_1922;
      v23 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
      v22 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
    }
    operator delete(block: v22, __formal: v23);
  }
  v24 = &v1079;
  UIControl::getPathedName(this: ownerControl, result: (const std::string *)&v1079);
  memset(&defaultValue, 0, 32);
  v25 = (__m128i *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                     this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                     a2: 32);
  if ( v25 == nullptr )
    `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
  *(_QWORD *)&defaultValue.mFileSystem = v25;
  *(_QWORD *)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Alias[8] = 17;
  defaultValue.mPath.mContainer._Mypair._Myval2._Mysize = 31;
  *v25 = _mm_loadu_si128(&xmmword_14EFA683D);
  v25[1].m128i_i16[0] = 32;
  v27 = *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
  if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
    v24 = *(UIResolvedDef **)&v1079.mIgnored;
  if ( *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= 0xEu )
  {
    *(_QWORD *)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Alias[8] = *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8]
                                                                            + 17LL;
    memmove_0(a1: &v25[1].m128i_i8[1], Src: v24, Size: *(size_t *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8]);
    v25[1].m128i_i8[v27 + 1] = 0;
    p_defaultValue = (const __m128i *)&defaultValue;
  }
  else
  {
    p_defaultValue = (const __m128i *)____Reallocate_grow_by_V_lambda_1___0__append___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD_K___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__append_01_QEAAAEAV01_QEBD0_Z_PEBD_K_Z(
                                        this: (std::string *)&defaultValue,
                                        _Size_increase: *(const unsigned __int64 *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8],
                                        _Fn: v26,
                                        _Args: (const char *)&v24->mIgnored,
                                        a5: *(unsigned __int64 *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8]);
  }
  v29 = _mm_loadu_si128(p_defaultValue);
  *(__m128i *)((char *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx + 8) = _mm_loadu_si128(p_defaultValue + 1);
  *(__m128i *)&_Args[0].mIgnored = v29;
  p_defaultValue[1].m128i_i64[0] = 0;
  p_defaultValue[1].m128i_i64[1] = 15;
  p_defaultValue->m128i_i8[0] = 0;
  if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize < 0x10 )
    v30 = _Args;
  else
    v30 = *(UIResolvedDef **)&_Args[0].mIgnored;
  v31 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
  v1106._Mypair._Myval2._Bx._Ptr = nullptr;
  if ( v30 != nullptr )
  {
    v32 = (size_t *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_alignedAllocate(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                      a2: *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] + 9LL,
                      a3: 8);
    v33 = v32;
    if ( v31 != -9 && v32 == nullptr )
      `anonymous namespace'::MemoryAnon::reportBadAlloc(size: v31 + 9, alignment: 8u);
    *v33 = v31;
    memcpy_0(a1: v33 + 1, Src: v30, Size: v31);
    *((_BYTE *)v33 + v31 + 8) = 0;
    v34 = (char *)((unsigned __int64)(v33 + 1) & 0xFF00FFFFFFFFFFFFuLL | 0x80000000000000LL);
  }
  else
  {
    v34 = (char *)((unsigned __int64)(_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 0x7F) << 48);
  }
  v1106._Mypair._Myval2._Bx._Ptr = v34;
  LOBYTE(Src._Mypair._Myval2._Mysize) = 0;
  ContentLog::ContentLogScope::ContentLogScope(
    this: &v1008,
    ref: (std::optional<std::string_view > *)&Src,
    str: (const Bedrock::StaticOptimizedString *)&v1106);
  if ( ((__int64)v1106._Mypair._Myval2._Bx._Ptr & 0x80000000000000LL) != 0 )
    ((void (__fastcall *)(Bedrock::Memory::IMemoryAllocator *, unsigned __int64))Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_alignedRelease)(
      a1: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
      a2: ((unsigned __int64)v1106._Mypair._Myval2._Bx._Ptr & 0xFF00FFFFFFFFFFFFuLL) - 8);
  v1106._Mypair._Myval2._Bx._Ptr = nullptr;
  if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
  {
    v35 = *(void **)&_Args[0].mIgnored;
    v36 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
    if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
        goto LABEL_1922;
      v36 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
      v35 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
    }
    operator delete(block: v35, __formal: v36);
  }
  *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] = 0;
  _Args[0].mDefNamespace._Mypair._Myval2._Mysize = 15;
  _Args[0].mIgnored = false;
  if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
  {
    v37 = *(void **)&defaultValue.mFileSystem;
    v38 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
    if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                            - 8LL
                            - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
        goto LABEL_1922;
      v38 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
      v37 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
    }
    operator delete(block: v37, __formal: v38);
  }
  if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
  {
    v39 = *(void **)&v1079.mIgnored;
    v40 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
    if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
    {
      if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
        goto LABEL_1922;
      v40 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
      v39 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
    }
    operator delete(block: v39, __formal: v40);
  }
  LODWORD(v41) = UIResolvedDef::getDefType(this: v1110);
  switch ( v41 )
  {
    case 0LL:
      v42 = v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateButtonComponent(def: v42, ownerControl: v43);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v42);
      UIControlFactory::_populateFocusComponent(def, ownerControl: (UIControl *)v42);
      UIControlFactory::_populateInputComponent(def, ownerControl: (UIControl *)v42);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: (UIControl *)v42);
      UIControlFactory::_populateSoundComponent(def, ownerControl: (UIControl *)v42, a3: (bool)v43);
      UIControlFactory::_populateTextToSpeechComponent(def: v42, ownerControl: v43, controlPriorityDefault: 1000);
      goto LABEL_1734;
    case 1LL:
      v148 = v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      LOBYTE(v149) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v149);
      *(_QWORD *)&defaultValue.mFileSystem = u;
      defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = nullptr;
      Src._Mypair._Myval2._Bx._Ptr = (char *)"renderer";
      *(_QWORD *)&Src._Mypair._Myval2._Bx._Alias[8] = 8;
      v150 = _Args;
      UIResolvedDef::getAsString(
        this: v148,
        result: (std::string *)_Args,
        key: (std::string_view *)&Src,
        (std::string_view *)&defaultValue);
      v151 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 80);
      if ( v151 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x50u, alignment: 0);
      v152 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v151 + 1) = ownerControl;
      v151[16] = 0;
      *(_QWORD *)(v151 + 20) = 0;
      *((_DWORD *)v151 + 7) = 1065353216;
      *(_QWORD *)v151 = &CustomRenderComponent::`vftable';
      *((_OWORD *)v151 + 2) = 0;
      *((_OWORD *)v151 + 3) = 0;
      *((_QWORD *)v151 + 8) = 0;
      *((_QWORD *)v151 + 9) = 15;
      if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,CustomRenderComponent>'::`2'::id = _InterlockedExchangeAdd64(
                                                                         (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                         1u);
          qword_151E0BEB8 = 1LL << `uicontrol_id<UIComponent,CustomRenderComponent>'::`2'::id;
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v153 = qword_151E0BEB8;
      Myval2 = v152[22]._Mypair._Myval2;
      v155 = (((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1))
            - ((((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v156 = (0x101010101010101LL
            * ((v155
              + (((((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1))
                 - ((((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v155
                + (((((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1))
                   - ((((unsigned __int64)Myval2 & (qword_151E0BEB8 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v157 = v152 + 23;
      if ( (qword_151E0BEB8 & (unsigned __int64)Myval2) != 0 )
      {
        v158 = *((RenderableComponent **)&v157->_Mypair._Myval2->__vftable + v156);
        v1067 = v151;
        v159 = guard_dispatch_icall_nop(a1: v158);
        v1067 = v151;
        v160 = guard_dispatch_icall_nop(a1: v158);
        if ( (v160 | v159) == 1 )
        {
          if ( v159 != 0 )
          {
            Myfirst = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            Mylast = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( Myfirst != Mylast )
            {
              while ( *Myfirst != v158 )
              {
                if ( ++Myfirst == Mylast )
                  goto LABEL_453;
              }
            }
            if ( Myfirst != Mylast )
            {
              v396 = v160;
              memmove_0(a1: Myfirst, Src: Myfirst + 1, Size: (char *)Mylast - (char *)(Myfirst + 1));
              v160 = v396;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_453:
          if ( v160 != 0 )
          {
            v397 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v398 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v397 != v398 )
            {
              while ( *v397 != (CustomFrameUpdateComponent *)v158 )
              {
                if ( ++v397 == v398 )
                  goto LABEL_460;
              }
            }
            if ( v397 != v398 )
            {
              memmove_0(a1: v397, Src: v397 + 1, Size: (char *)v398 - (char *)(v397 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_460:
        v399 = *((void (__fastcall ****)(_QWORD, __int64))&v157->_Mypair._Myval2->__vftable + v156);
        *((_QWORD *)&v157->_Mypair._Myval2->__vftable + v156) = v151;
        if ( v399 != nullptr )
          (**v399)(a1: v399, a2: 1);
LABEL_742:
        v1067 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v151) != 0 )
        {
          *(_QWORD *)&v1079.mIgnored = v151;
          v519 = ownerControl;
          v520 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v520 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1067 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v520);
          }
          else
          {
            *v520 = (RenderableComponent *)v151;
            ++v519->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1067 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v151) != 0 )
        {
          *(_QWORD *)&v1079.mIgnored = v151;
          v521 = ownerControl;
          v522 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v522 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1067 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v522);
          }
          else
          {
            *v522 = (CustomFrameUpdateComponent *)v151;
            ++v521->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,CustomRenderComponent>'::`2'::id = _InterlockedExchangeAdd64(
                                                                           (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                           1u);
            qword_151E0BEB8 = 1LL << `uicontrol_id<UIComponent,CustomRenderComponent>'::`2'::id;
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomRenderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        mComponentsInUse = ownerControl->mComponentsInUse;
        p_mPath = (Core::PathBuffer<std::string > *)v157;
        if ( (qword_151E0BEB8 & mComponentsInUse) != 0
          && (v525 = ((qword_151E0BEB8 - 1) & mComponentsInUse)
                   - ((((qword_151E0BEB8 - 1) & mComponentsInUse) >> 1) & 0x5555555555555555LL),
              v526 = (0x101010101010101LL
                    * (((v525 & 0x3333333333333333LL)
                      + ((v525 >> 2) & 0x3333333333333333LL)
                      + (((v525 & 0x3333333333333333LL) + ((v525 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v527 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v527 > v526) )
        {
          v528 = (CustomRenderComponent *)v527[v526]._Mypair._Myval2;
        }
        else
        {
          v528 = nullptr;
        }
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v150 = *(UIResolvedDef **)&_Args[0].mIgnored;
        switch ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] )
        {
          case 0x11LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(
                       _mm_cvtsi32_si128((unsigned __int8)v150->mDefNamespace._Mypair._Myval2._Bx._Buf[8]),
                       (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm))) != 0xFFFF )
              goto LABEL_802;
            v529 = (__m128i *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                a2: 128);
            if ( v529 == nullptr )
              `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x80u, alignment: 0);
            v529->m128i_i64[1] = 0x100000001LL;
            v529->m128i_i64[0] = (__int64)&std::_Ref_count_obj2<Editor::Network::KeyBindingStatePayload>::`vftable';
            v529[1].m128i_i32[2] = 1065353216;
            v529[1].m128i_i64[0] = (__int64)&NameTagRenderer::`vftable';
            v529[2].m128i_i8[9] = 0;
            v529[2].m128i_i16[5] = 0;
            v529[2].m128i_i32[3] = 0;
            v529[3].m128i_i64[0] = 11;
            v529[3].m128i_i64[1] = 15;
            strcpy(v529[2].m128i_i8, "#playern");
            v529[4] = 0;
            v529[5].m128i_i64[0] = 0;
            v529[5].m128i_i64[1] = 15;
            v529[6] = (__m128i)_xmm;
            v529[7] = _mm_load_si128((const __m128i *)&_xmm);
            v1106._Mypair._Myval2._Bx._Ptr = v529[1].m128i_i8;
            *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = v529;
            *(_QWORD *)&v1079.mIgnored = "text_color";
            v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)10;
            Value = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1079, a3: false);
            if ( Json::Value::operator!=(this: Value, other: &Json::Value::null) )
            {
              v1069._Mypair._Myval2._Bx._Ptr = "text_color";
              *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 10;
              UIResolvedDef::getAsColor(
                this: v1110,
                result: (mce::Color *)&v1079,
                key: (std::string_view *)&v1069,
                defaultValue: &Palette::WHITE);
              v529[6] = _mm_loadu_si128((const __m128i *)&v1079);
            }
            *(_QWORD *)&v1079.mIgnored = "background_color";
            v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)16;
            v531 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1079, a3: false);
            if ( Json::Value::operator!=(this: v531, other: &Json::Value::null) )
            {
              __formal._Mypair._Myval2._Bx._Ptr = "background_color";
              *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 16;
              UIResolvedDef::getAsColor(
                this: v1110,
                result: (mce::Color *)&v1079,
                key: (std::string_view *)&__formal,
                defaultValue: &Palette::WHITE);
              v529[7] = _mm_loadu_si128((const __m128i *)&v1079);
            }
            v1106._Mypair._Myval2._Bx = 0;
            _InterlockedIncrement(&v529->m128i_i32[2]);
            v528->mRenderer._Ptr = (UICustomRenderer *)&v529[1];
            Rep = (volatile signed __int32 *)v528->mRenderer._Rep;
            v528->mRenderer._Rep = (std::_Ref_count_base *)v529;
            if ( Rep != nullptr && _InterlockedDecrement(Rep + 2) == 0 )
            {
              (**(void (__fastcall ***)(volatile signed __int32 *))Rep)(a1: Rep);
              if ( _InterlockedDecrement(Rep + 3) == 0 )
                (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)Rep + 8LL))(a1: Rep);
            }
            if ( _InterlockedDecrement(&v529->m128i_i32[2]) == 0 )
            {
              (*(void (__fastcall **)(__m128i *))v529->m128i_i64[0])(a1: v529);
              if ( _InterlockedDecrement(&v529->m128i_i32[3]) == 0 )
                (*(void (__fastcall **)(__m128i *))(v529->m128i_i64[0] + 8))(a1: v529);
            }
            v533 = *(std::_Ref_count_base **)&v1106._Mypair._Myval2._Bx._Alias[8];
            if ( *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] != 0
              && _InterlockedDecrement((volatile signed __int32 *)(*(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] + 8LL)) == 0 )
            {
              v533->_Destroy(this: v533);
              if ( _InterlockedDecrement((volatile signed __int32 *)&v533->_Weaks) == 0 )
                goto LABEL_1831;
            }
            goto LABEL_1839;
          case 0x13LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 32);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<EditorGizmoRenderer>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              v533[1]._Uses = 1065353216;
              v956 = &BackgroundRenderer::`vftable';
              goto LABEL_1824;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 32);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<EditorGizmoRenderer>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              v533[1]._Uses = 1065353216;
              v956 = &TrialTimerTextRenderer::`vftable';
              goto LABEL_1824;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 32);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<EditorGizmoRenderer>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              v533[1]._Uses = 1065353216;
              v956 = &LiveHorseRenderer::`vftable';
              goto LABEL_1824;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 64);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x40u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<Bedrock::PubSub::Publisher<void (std::optional<unsigned __int64>),Bedrock::PubSub::ThreadModel::SingleThreaded,0>>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              v533[1]._Uses = 1065353216;
              v533[1].__vftable = (std::_Ref_count_base_vtbl *)&HudPlayerRenderer::`vftable';
              v533[2] = 0;
              v533[3] = 0;
              goto LABEL_1825;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) == 0xFFFF )
            {
              *(_QWORD *)&v1079.mIgnored = &PaperDollResolvedUIDefSource::`vftable';
              v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)&v1110->mIgnored;
              v998 = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 416);
              if ( v998 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x1A0u, alignment: 0);
              v998[1] = 0x100000001LL;
              *v998 = &std::_Ref_count_obj2<BackgroundTask<void,nonstd::expected_lite::expected<std::optional<std::string>,Bedrock::Threading::CachedAsyncRetry>>>::`vftable';
              v1080 = (UIComponent *)v998;
              v999 = (PaperDollRenderer *)(v998 + 2);
              PaperDollRenderer::PaperDollRenderer(this: v999, def: (const IPaperDollUIDefSource *)&v1079);
              v957 = v1080;
              p_mOwner = (volatile signed __int32 *)&v1080->mOwner;
              _InterlockedIncrement((volatile signed __int32 *)&v1080->mOwner);
              v528->mRenderer._Ptr = v999;
              v1001 = (volatile signed __int32 *)v528->mRenderer._Rep;
              v528->mRenderer._Rep = (std::_Ref_count_base *)v957;
              if ( v1001 != nullptr && _InterlockedDecrement(v1001 + 2) == 0 )
              {
                (**(void (__fastcall ***)(volatile signed __int32 *))v1001)(a1: v1001);
                if ( _InterlockedDecrement(v1001 + 3) == 0 )
                  (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v1001 + 8LL))(a1: v1001);
              }
              if ( _InterlockedDecrement(p_mOwner) == 0 )
                goto LABEL_1814;
            }
            else
            {
              if ( _mm_movemask_epi8(
                     _mm_and_si128(
                       _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                       _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 3)), (__m128i)_xmm))) != 0xFFFF )
                goto LABEL_802;
              std::make_shared_HoverTextRenderer_const_UIResolvedDef___(
                result: (std::shared_ptr<HoverTextRenderer> *)&v1106,
                _Args: v1110);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
            }
            goto LABEL_1839;
          case 0x14LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(
                       _mm_cvtsi32_si128(*(_DWORD *)&v150->mDefNamespace._Mypair._Myval2._Bx._Alias[8]),
                       (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 32);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<Social::`anonymous namespace'::MultiplayerServiceStateReporterAnon::MinecraftEventingCallbacks>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              v533[1]._Uses = 1065353216;
              v956 = &LivePlayerRenderer::`vftable';
              goto LABEL_1824;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(
                       _mm_cvtsi32_si128(*(_DWORD *)&v150->mDefNamespace._Mypair._Myval2._Bx._Alias[8]),
                       (__m128i)_xmm))) != 0xFFFF )
              goto LABEL_802;
            v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                             this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                             a2: 88);
            if ( v533 == nullptr )
              `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x58u, alignment: 0);
            p_Uses = (volatile signed __int32 *)&v533->_Uses;
            *(_QWORD *)&v533->_Uses = 0x100000001LL;
            v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<WireframeQueue>::`vftable';
            v535 = (UICustomRenderer *)&v533[1];
            v533[1]._Uses = 1065353216;
            v533[1].__vftable = (std::_Ref_count_base_vtbl *)&SplashTextRenderer::`vftable';
            LOBYTE(v533[4].__vftable) = 0;
            *(_QWORD *)&v533[4]._Uses = 0;
            LOBYTE(v533[5].__vftable) = 0;
            goto LABEL_1825;
          case 0x15LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 5)), (__m128i)_xmm))) == 0xFFFF )
            {
              v533 = (std::_Ref_count_base *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                               a2: 32);
              if ( v533 == nullptr )
                `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
              p_Uses = (volatile signed __int32 *)&v533->_Uses;
              *(_QWORD *)&v533->_Uses = 0x100000001LL;
              v533->__vftable = (std::_Ref_count_base_vtbl *)&std::_Ref_count_obj2<EditorGizmoRenderer>::`vftable';
              v535 = (UICustomRenderer *)&v533[1];
              *(_QWORD *)&v533[1]._Uses = 0;
              v533[1]._Uses = 1065353216;
              v956 = &DebugScreenRenderer::`vftable';
LABEL_1824:
              v533[1].__vftable = (std::_Ref_count_base_vtbl *)v956;
LABEL_1825:
              _InterlockedIncrement((volatile signed __int32 *)&v533->_Uses);
              v528->mRenderer._Ptr = v535;
              v962 = (volatile signed __int32 *)v528->mRenderer._Rep;
              v528->mRenderer._Rep = v533;
              if ( v962 != nullptr && _InterlockedDecrement(v962 + 2) == 0 )
              {
                (**(void (__fastcall ***)(volatile signed __int32 *))v962)(a1: v962);
                if ( _InterlockedDecrement(v962 + 3) == 0 )
                  (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v962 + 8LL))(a1: v962);
              }
              if ( _InterlockedDecrement(p_Uses) == 0 )
              {
                v533->_Destroy(this: v533);
                if ( _InterlockedDecrement((volatile signed __int32 *)&v533->_Weaks) == 0 )
LABEL_1831:
                  v533->_Delete_this(this: v533);
              }
              goto LABEL_1839;
            }
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 5)), (__m128i)_xmm))) == 0xFFFF )
            {
              std::make_shared_ProgressBarRenderer_(result: (std::shared_ptr<ProgressBarRenderer> *)&v1079);
              v1106._Mypair._Myval2._Bx._Ptr = "primary_color";
              *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = 13;
              if ( UIResolvedDef::hasValue(this: v1110, key: (std::string_view *)&v1106) )
              {
                v536 = *(__m128i **)&v1079.mIgnored;
                __formal._Mypair._Myval2._Bx._Ptr = "primary_color";
                *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 13;
                UIResolvedDef::getAsColor(
                  this: v1110,
                  result: (mce::Color *)&v1069,
                  key: (std::string_view *)&__formal,
                  defaultValue: &Palette::WHITE);
                v536[1] = _mm_loadu_si128((const __m128i *)&v1069);
              }
              v1069._Mypair._Myval2._Bx._Ptr = "secondary_color";
              *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 15;
              if ( UIResolvedDef::hasValue(this: v1110, key: (std::string_view *)&v1069) )
              {
                v537 = *(__m128i **)&v1079.mIgnored;
                v1073._Mypair._Myval2._Bx._Ptr = "secondary_color";
                *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 15;
                UIResolvedDef::getAsColor(
                  this: v1110,
                  result: (mce::Color *)&v1076,
                  key: (std::string_view *)&v1073,
                  defaultValue: &Palette::WHITE);
                v537[2] = _mm_loadu_si128((const __m128i *)&v1076);
              }
              v1076._Mypair._Myval2._Bx._Ptr = "full_storage_color";
              *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 18;
              if ( UIResolvedDef::hasValue(this: v1110, key: (std::string_view *)&v1076) )
              {
                v538 = *(__m128i **)&v1079.mIgnored;
                v1068._Mypair._Myval2._Bx._Ptr = "full_storage_color";
                *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 18;
                UIResolvedDef::getAsColor(
                  this: v1110,
                  result: (mce::Color *)&v1072,
                  key: (std::string_view *)&v1068,
                  defaultValue: &Palette::WHITE);
                v538[3] = _mm_loadu_si128((const __m128i *)&v1072);
                if ( v538[4].m128i_i8[0] == 0 )
                  v538[4].m128i_i8[0] = 1;
              }
              v1072._Mypair._Myval2._Bx = 0;
              if ( v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr != nullptr )
              {
                _InterlockedIncrement((volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr + 2);
                v539 = v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr;
              }
              else
              {
                v539 = nullptr;
              }
              v1072._Mypair._Myval2._Bx._Ptr = *(char **)&v1079.mIgnored;
              *(_QWORD *)&v1072._Mypair._Myval2._Bx._Alias[8] = v539;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1072);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1079);
              goto LABEL_1839;
            }
LABEL_802:
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "hotbar_renderer") )
            {
              std::make_shared_HotBarDropRenderer_(result: (std::shared_ptr<HotBarDropRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "hotbar_cooldown_renderer") )
            {
              std::make_shared_HotBarCooldownRenderer_(result: (std::shared_ptr<HotBarCooldownRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "flying_item_renderer") )
            {
              std::make_shared_FlyingItemRenderer_(result: (std::shared_ptr<FlyingItemRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "heart_renderer") )
            {
              std::make_shared_HudHeartRenderer_(result: (std::shared_ptr<HudHeartRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "horse_heart_renderer") )
            {
              std::make_shared_HudHorseHeartRenderer_(result: (std::shared_ptr<HudHorseHeartRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "armor_renderer") )
            {
              std::make_shared_HudArmorRenderer_(result: (std::shared_ptr<HudArmorRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "horse_jump_renderer") )
            {
              std::make_shared_HudHorseJumpRenderer_const_UIResolvedDef___(
                result: (std::shared_ptr<HudHorseJumpRenderer> *)&v1106,
                _Args: v1110);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "dash_renderer") )
            {
              std::make_shared_HudDashRenderer_const_UIResolvedDef___(
                result: (std::shared_ptr<HudDashRenderer> *)&v1106,
                _Args: v1110);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "locator_bar") )
            {
              std::make_shared_HudLocatorBarRenderer_(result: (std::shared_ptr<HudLocatorBarRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "hunger_renderer") )
            {
              std::make_shared_HudHungerRenderer_(result: (std::shared_ptr<HudHungerRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "bubbles_renderer") )
            {
              std::make_shared_HudBubblesRenderer_(result: (std::shared_ptr<HudBubblesRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "vignette_renderer") )
            {
              std::make_shared_HudVignetteRenderer_(result: (std::shared_ptr<HudVignetteRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "cursor_renderer") )
            {
              std::make_shared_HudCursorRenderer_(result: (std::shared_ptr<HudCursorRenderer> *)&v1106);
              *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
              v1106._Mypair._Myval2._Bx = 0;
              CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
              std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
              goto LABEL_1839;
            }
            break;
          case 0x17LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)(&v150->mIgnored + 7)), (__m128i)_xmm))) != 0xFFFF )
              goto LABEL_802;
            v957 = (UIComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                    this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                    a2: 480);
            if ( v957 == nullptr )
              `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x1E0u, alignment: 0);
            v957->mOwner = (UIControl *)0x100000001LL;
            v957->__vftable = (UIComponent_vtbl *)&std::_Ref_count_obj2<Social::GameCorePlatformIdentity>::`vftable';
            LODWORD(v957[1].mOwner) = 1065353216;
            v957[1].__vftable = (UIComponent_vtbl *)&MinecraftUICustomRenderer::`vftable';
            v1031 = v957 + 2;
            v957[2].__vftable = (UIComponent_vtbl *)&ActorShaderManager::`vftable';
            *(_OWORD *)&v957[2].mOwner = 0;
            *(_OWORD *)&v957[3].mOwner = 0;
            *(_OWORD *)&v957[4].mOwner = 0;
            v1080 = v957;
            InventoryItemRenderItemData::InventoryItemRenderItemData(this: (InventoryItemRenderItemData *)&v957[5].mOwner);
            v958 = v1080;
            v959 = (volatile signed __int32 *)&v1080->mOwner;
            v960 = (UICustomRenderer *)&v1080[1];
            v1080[1].__vftable = (UIComponent_vtbl *)&InventoryItemRenderer::`vftable'{for `MinecraftUICustomRenderer'};
            v958[2].__vftable = (UIComponent_vtbl *)&InventoryItemRenderer::`vftable'{for `ActorShaderManager'};
            *(__m128i *)&v958[27].mOwner = _mm_load_si128((const __m128i *)&_xmm_ffffffff00000000ffffffffffffffff);
            LOBYTE(v958[28].mOwner) = 0;
            v958[29].__vftable = nullptr;
            LOBYTE(v958[29].mOwner) = 0;
            _InterlockedIncrement((volatile signed __int32 *)&v958->mOwner);
            v528->mRenderer._Ptr = v960;
            v961 = (volatile signed __int32 *)v528->mRenderer._Rep;
            v528->mRenderer._Rep = (std::_Ref_count_base *)v958;
            if ( v961 != nullptr && _InterlockedDecrement(v961 + 2) == 0 )
            {
              (**(void (__fastcall ***)(volatile signed __int32 *))v961)(a1: v961);
              if ( _InterlockedDecrement(v961 + 3) == 0 )
                (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v961 + 8LL))(a1: v961);
            }
            if ( _InterlockedDecrement(v959) == 0 )
            {
LABEL_1814:
              v957->dtr_UIComponent(this: v957);
              if ( _InterlockedDecrement((volatile signed __int32 *)&v957->mOwner + 1) == 0 )
                ((void (__fastcall *)(UIComponent *))v957->clone)(a1: v957);
            }
            goto LABEL_1839;
          case 0x18LL:
            if ( _mm_movemask_epi8(
                   _mm_and_si128(
                     _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v150), (__m128i)_xmm),
                     _mm_cmpeq_epi8(
                       _mm_loadl_epi64((const __m128i *)&v150->mDefNamespace._Mypair._Myval2._Bx._Alias[8]),
                       (__m128i)_xmm))) != 0xFFFF )
              goto LABEL_802;
            std::make_shared_EnchantingBookRenderer_(result: (std::shared_ptr<EnchantingBookRenderer> *)&v1106);
            *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
            v1106._Mypair._Myval2._Bx = 0;
            CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
            std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
            goto LABEL_1839;
          default:
            goto LABEL_802;
        }
LABEL_1920:
        if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "progress_indicator_renderer") )
        {
          std::make_shared_HudProgressRenderer_(result: (std::shared_ptr<HudProgressRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "mob_effects_renderer") )
        {
          std::make_shared_HudMobEffectsRenderer_(result: (std::shared_ptr<HudMobEffectsRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "camera_renderer") )
        {
          std::make_shared_HudCameraRenderer_(result: (std::shared_ptr<HudCameraRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "equipment_preview_renderer") )
        {
          std::make_shared_EquipmentPreviewRenderer_const_UIResolvedDef___(
            result: (std::shared_ptr<EquipmentPreviewRenderer> *)&v1106,
            _Args: v1110);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "gradient_renderer") )
        {
          UIControlFactory::_createGradientRenderer(customRenderComponent: v528, def: v1110);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "panorama_renderer") )
        {
          UIControlFactory::_populateSpriteComponent(def, ownerControl: (UIControl *)v1110);
          UIControlFactory::_populateGestureComponent(def: v1110, ownerControl);
          std::make_shared_PanoramaRenderer_const_UIResolvedDef___(
            result: (std::shared_ptr<PanoramaRenderer> *)&v1106,
            _Args: v1110);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "3d_structure_renderer") )
        {
          std::make_shared_StructureVolumeRenderer_(result: (std::shared_ptr<StructureVolumeRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "bohr_model_renderer") )
        {
          std::make_shared_BohrModelRenderer_(result: (std::shared_ptr<BohrModelRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "web_view_renderer") )
        {
          std::make_shared_WebViewRenderer_(result: (std::shared_ptr<WebViewRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "actor_portrait_renderer") )
        {
          std::make_shared_ActorPortraitRenderer_(result: (std::shared_ptr<ActorPortraitRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "animated_gif_renderer") )
        {
          std::make_shared_AnimatedGifRenderer_(result: (std::shared_ptr<AnimatedGifRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "banner_pattern_renderer") )
        {
          std::make_shared_BannerPatternRenderer_(result: (std::shared_ptr<BannerPatternRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "credits_renderer") )
        {
          std::make_shared_CreditsRenderer_const_UIResolvedDef___(
            result: (std::shared_ptr<CreditsRenderer> *)&v1106,
            _Args: v1110);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "qr_code_renderer") )
        {
          std::make_shared_QRCodeRenderer_(result: (std::shared_ptr<QRCodeRenderer> *)&v1079);
          v1106._Mypair._Myval2._Bx._Ptr = "background_color";
          *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = 16;
          if ( UIResolvedDef::hasValue(this: v1110, key: (std::string_view *)&v1106) )
          {
            v1002 = *(__m128i **)&v1079.mIgnored;
            __formal._Mypair._Myval2._Bx._Ptr = "background_color";
            *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 16;
            UIResolvedDef::getAsColor(
              this: v1110,
              result: (mce::Color *)&v1069,
              key: (std::string_view *)&__formal,
              defaultValue: &Palette::WHITE);
            v1002[4] = _mm_loadu_si128((const __m128i *)&v1069);
            v1003 = v1002[5].m128i_i64[1];
            if ( v1003 != 0 )
              *(_BYTE *)(v1003 + 18) = 0;
          }
          v1069._Mypair._Myval2._Bx._Ptr = "foreground_color";
          *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 16;
          if ( UIResolvedDef::hasValue(this: v1110, key: (std::string_view *)&v1069) )
          {
            v1004 = *(__m128i **)&v1079.mIgnored;
            v1073._Mypair._Myval2._Bx._Ptr = "foreground_color";
            *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 16;
            UIResolvedDef::getAsColor(
              this: v1110,
              result: (mce::Color *)&v1076,
              key: (std::string_view *)&v1073,
              defaultValue: &Palette::WHITE);
            v1004[3] = _mm_loadu_si128((const __m128i *)&v1076);
            v1005 = v1004[5].m128i_i64[1];
            if ( v1005 != 0 )
              *(_BYTE *)(v1005 + 18) = 0;
          }
          v1076._Mypair._Myval2._Bx = 0;
          if ( v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr != nullptr )
          {
            _InterlockedIncrement((volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr + 2);
            v1006 = v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr;
          }
          else
          {
            v1006 = nullptr;
          }
          v1076._Mypair._Myval2._Bx._Ptr = *(char **)&v1079.mIgnored;
          *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = v1006;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1076);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1079);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "profile_image_renderer") )
        {
          std::make_shared_ProfileImageRenderer_(result: (std::shared_ptr<ProfileImageRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "editor_gizmo_renderer") )
        {
          std::make_shared_EditorGizmoRenderer_(result: (std::shared_ptr<EditorGizmoRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "editor_volume_highlight_renderer") )
        {
          std::make_shared_EditorVolumeHighlightRenderer_(result: (std::shared_ptr<EditorVolumeHighlightRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "editor_compass_renderer") )
        {
          std::make_shared_EditorCompassRenderer_(result: (std::shared_ptr<EditorCompassRenderer> *)&v1106);
          *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
          v1106._Mypair._Myval2._Bx = 0;
          CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
          std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
        }
        else
        {
          v1007 = _Args;
          if ( std::operator==<char>(_Left: (const std::string *)_Args, _Right: "bundle_tooltip_renderer") )
          {
            std::make_shared_CursorPositionLayoutUpdater_(result: (std::shared_ptr<CursorPositionLayoutUpdater> *)&v1106);
            *(__m128i *)&v1079.mIgnored = _mm_load_si128((const __m128i *)&v1106);
            v1106._Mypair._Myval2._Bx = 0;
            CustomRenderComponent::setRenderer(this: v528, renderer: (std::shared_ptr<UICustomRenderer> *)&v1079);
            std::shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>::~shared_ptr<Bedrock::Threading::IAsyncResult<Social::XboxLiveUserProfileData>>(this: (std::shared_ptr<dragon::MaterialDescription> *)&v1106);
          }
          else
          {
            if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
              v1007 = *(UIResolvedDef **)&_Args[0].mIgnored;
            *(_QWORD *)&v1079.mIgnored = v1007;
            ContentLogHelper::_contentLog<char const (&)[45],char const * &>(
              level: true,
              area: (const LogLevel)3,
              args: UI,
              a4: (const char (*)[15])"Unrecognized renderer: '%s'",
              a5: (const char **)&v1079);
          }
        }
LABEL_1839:
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v963 = *(void **)&_Args[0].mIgnored;
          v964 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v964 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
            v963 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
          }
          operator delete(block: v963, __formal: v964);
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1108);
        LOBYTE(v965) = 27;
        LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                          a2: (Memory::MemoryCategory)v965);
        *(_QWORD *)&v1079.mIgnored = u;
        v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = nullptr;
        *(_QWORD *)&defaultValue.mFileSystem = "renderer";
        defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = (char *)8;
        v966 = _Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: (std::string_view *)&defaultValue,
          defaultValue: (std::string_view *)&v1079);
        v967 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 27 )
          goto LABEL_1891;
        v968 = (std::unique_ptr<StructureFeature> *)p_mPath;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v966 = *(UIResolvedDef **)&_Args[0].mIgnored;
        if ( _mm_movemask_epi8(
               _mm_and_si128(
                 _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)v966), (__m128i)_xmm),
                 _mm_cmpeq_epi8(
                   _mm_loadu_si128((const __m128i *)&v966->mDefNamespace._Mypair._Myval2._Bx._Alias[3]),
                   (__m128i)_xmm))) != 0xFFFF )
          goto LABEL_1891;
        v969 = (RenderableComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                        a2: 16);
        if ( v969 == nullptr )
          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x10u, alignment: 0);
        v970 = ownerControl;
        v969->mOwner = ownerControl;
        v969->__vftable = (RenderableComponent_vtbl *)&CustomFrameUpdateComponent::`vftable';
        if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomFrameUpdateComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomFrameUpdateComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VCustomFrameUpdateComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                                    (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                                    1u);
            `uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VCustomFrameUpdateComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        mBitId = `uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId;
        v972 = v970->mComponentsInUse;
        v973 = ((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1))
              - (((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1)) >> 1)
               & 0x5555555555555555LL))
             & 0x3333333333333333LL;
        v974 = (0x101010101010101LL
              * ((v973
                + ((((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1))
                   - (((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1)) >> 1)
                    & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)
                + ((v973
                  + ((((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1))
                     - (((v972 & (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId - 1)) >> 1)
                      & 0x5555555555555555LL)) >> 2)
                   & 0x3333333333333333LL)) >> 4))
               & 0xF0F0F0F0F0F0F0FLL)) >> 56;
        if ( (`uicontrol_id<UIComponent,CustomFrameUpdateComponent>'::`2'::id.mBitId & v972) != 0 )
        {
          v975 = *((RenderableComponent **)&v968->_Mypair._Myval2->__vftable + v974);
          v1066 = v969;
          v976 = guard_dispatch_icall_nop(a1: v975);
          v1066 = v969;
          v977 = guard_dispatch_icall_nop(a1: v975);
          if ( (v977 | v976) == 1 )
          {
            if ( v976 != 0 )
            {
              v978 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
              v979 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
              if ( v978 != v979 )
              {
                while ( *v978 != v975 )
                {
                  if ( ++v978 == v979 )
                    goto LABEL_1871;
                }
              }
              if ( v978 != v979 )
              {
                v987 = v977;
                memmove_0(a1: v978, Src: v978 + 1, Size: (char *)v979 - (char *)(v978 + 1));
                v977 = v987;
                --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
              }
            }
LABEL_1871:
            if ( v977 != 0 )
            {
              v988 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
              v989 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
              if ( v988 != v989 )
              {
                while ( *v988 != (CustomFrameUpdateComponent *)v975 )
                {
                  if ( ++v988 == v989 )
                    goto LABEL_1878;
                }
              }
              if ( v988 != v989 )
              {
                memmove_0(a1: v988, Src: v988 + 1, Size: (char *)v989 - (char *)(v988 + 1));
                --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
              }
            }
          }
LABEL_1878:
          v990 = *((void (__fastcall ****)(_QWORD, __int64))&v968->_Mypair._Myval2->__vftable + v974);
          *((_QWORD *)&v968->_Mypair._Myval2->__vftable + v974) = v969;
          if ( v990 != nullptr )
            (**v990)(a1: v990, a2: 1);
          goto LABEL_1882;
        }
        Src._Mypair._Myval2._Bx._Ptr = (char *)v969;
        v980 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v970->mComponents._Mypair._Myval2._Myfirst
                                                      + (unsigned int)(8 * v974));
        v981 = v970->mComponents._Mypair._Myval2._Mylast;
        if ( v981 == v970->mComponents._Mypair._Myval2._Myend )
        {
          std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
            _Whereptr: v968,
            _Val: v980);
          v986 = Src._Mypair._Myval2._Bx._Ptr;
        }
        else
        {
          if ( v981 == (std::unique_ptr<UIComponent> *)v980 )
          {
            v981->_Mypair._Myval2 = v969;
            ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1881:
            ownerControl->mComponentsInUse |= mBitId;
LABEL_1882:
            v1066 = nullptr;
            if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v969) != 0 )
            {
              Src._Mypair._Myval2._Bx._Ptr = (char *)v969;
              v991 = ownerControl;
              v992 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
              if ( v992 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
              {
                v1066 = nullptr;
                std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
                  _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
                  _Val: (bgfx::d3d12::BufferHeapBlock *const *)v992);
              }
              else
              {
                *v992 = v969;
                ++v991->mRenderableComponentLookup._Mypair._Myval2._Mylast;
              }
            }
            v1066 = nullptr;
            if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v969) != 0 )
            {
              Src._Mypair._Myval2._Bx._Ptr = (char *)v969;
              v993 = ownerControl;
              v994 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
              if ( v994 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
              {
                v1066 = nullptr;
                std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
                  _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
                  _Val: (bgfx::d3d12::BufferHeapBlock *const *)v994);
              }
              else
              {
                *v994 = (CustomFrameUpdateComponent *)v969;
                ++v993->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
              }
            }
            v967 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
LABEL_1891:
            if ( v967 < 0x10 )
            {
LABEL_1896:
              Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                a2: (Memory::MemoryCategory)v1108);
              v997 = (UIControl *)v1110;
              v43 = ownerControl;
              UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v1110);
              UIControlFactory::_populateLayoutComponent(def, ownerControl: v997);
              UIControlFactory::_populateTextToSpeechComponent(
                def: (const UIResolvedDef *)v997,
                ownerControl: v43,
                controlPriorityDefault: 0);
              goto LABEL_1734;
            }
            v995 = *(void **)&_Args[0].mIgnored;
            v996 = v967 + 1;
            if ( v967 + 1 < 0x1000 )
            {
LABEL_1895:
              operator delete(block: v995, __formal: v996);
              goto LABEL_1896;
            }
            if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) < 0x20 )
            {
              v996 = v967 + 40;
              v995 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
              goto LABEL_1895;
            }
LABEL_1922:
            _invoke_watson(Expression: nullptr, FunctionName: nullptr, FileName: nullptr, LineNo: 0, Reserved: 0);
          }
          v982 = (std::unique_ptr<RuinedPortalFeature> *)&v981[-1];
          v983 = v981[-1]._Mypair._Myval2;
          v981[-1]._Mypair._Myval2 = nullptr;
          v981->_Mypair._Myval2 = v983;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
          while ( v982 != v980 )
          {
            v984 = v982[-1]._Mypair._Myval2;
            v985 = v982->_Mypair._Myval2;
            v982[-1]._Mypair._Myval2 = nullptr;
            v982->_Mypair._Myval2 = v984;
            if ( v985 != nullptr )
              ((void (__fastcall *)(RuinedPortalFeature *, __int64))v985->dtr_StructureFeature)(a1: v985, a2: 1);
            --v982;
          }
          v986 = (char *)v980->_Mypair._Myval2;
          v980->_Mypair._Myval2 = (RuinedPortalFeature *)v969;
        }
        if ( v986 != nullptr )
          (**(void (__fastcall ***)(char *, __int64))v986)(a1: v986, a2: 1);
        goto LABEL_1881;
      }
      *(_QWORD *)&v1079.mIgnored = v151;
      v282 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v152[23]._Mypair._Myval2 + (unsigned int)(8 * v156));
      v283 = v152[24]._Mypair._Myval2;
      if ( v283 == v152[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v152 + 23,
          _Val: v282);
        v378 = *(RuinedPortalFeature **)&v1079.mIgnored;
      }
      else
      {
        if ( v283 == (StructureFeature *)v282 )
        {
          v283->__vftable = (StructureFeature_vtbl *)v151;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_741:
          ownerControl->mComponentsInUse |= v153;
          goto LABEL_742;
        }
        p_mActiveBlueprintCreateCount = (std::unique_ptr<RuinedPortalFeature> *)&v283[-1].mActiveBlueprintCreateCount;
        v285 = *(StructureFeature_vtbl **)&v283[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v283[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v283->__vftable = v285;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( p_mActiveBlueprintCreateCount != v282 )
        {
          v286 = p_mActiveBlueprintCreateCount[-1]._Mypair._Myval2;
          v287 = p_mActiveBlueprintCreateCount->_Mypair._Myval2;
          p_mActiveBlueprintCreateCount[-1]._Mypair._Myval2 = nullptr;
          p_mActiveBlueprintCreateCount->_Mypair._Myval2 = v286;
          if ( v287 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v287->dtr_StructureFeature)(a1: v287, a2: 1);
          --p_mActiveBlueprintCreateCount;
        }
        v378 = v282->_Mypair._Myval2;
        v282->_Mypair._Myval2 = (RuinedPortalFeature *)v151;
      }
      if ( v378 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v378->dtr_StructureFeature)(a1: v378, a2: 1);
      goto LABEL_741;
    case 2LL:
      v118 = v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateCollectionComponent(def: v118, ownerControl: v43);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v118);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: (UIControl *)v118);
      goto LABEL_1734;
    case 3LL:
      v132 = (UIControl *)v1110;
      v133 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v132);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v132);
      UIControlFactory::_populateInputComponent(def, ownerControl: v132);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v132);
      UIControlFactory::_populateSoundComponent(def, ownerControl: v132, a3: (bool)v133);
      UIControlFactory::_populateToggleComponent(def: (const UIResolvedDef *)v132, ownerControl: v133);
      LOBYTE(v134) = 27;
      LOBYTE(def) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                      a2: (Memory::MemoryCategory)v134);
      v135 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 56);
      if ( v135 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x38u, alignment: 0);
      v136 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v135 + 1) = ownerControl;
      *(_QWORD *)v135 = &DropdownComponent::`vftable';
      *((_DWORD *)v135 + 4) = 0;
      *(_OWORD *)(v135 + 24) = 0;
      *(_OWORD *)(v135 + 40) = 0;
      if ( dword_151E0C928 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C928);
        if ( dword_151E0C928 == -1 )
        {
          qword_151E0C920 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C928);
        }
      }
      v137 = qword_151E0C920;
      v138 = v136[22]._Mypair._Myval2;
      v139 = (((unsigned __int64)v138 & (qword_151E0C920 - 1))
            - ((((unsigned __int64)v138 & (qword_151E0C920 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v140 = (0x101010101010101LL
            * ((v139
              + (((((unsigned __int64)v138 & (qword_151E0C920 - 1))
                 - ((((unsigned __int64)v138 & (qword_151E0C920 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v139
                + (((((unsigned __int64)v138 & (qword_151E0C920 - 1))
                   - ((((unsigned __int64)v138 & (qword_151E0C920 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v141 = v136 + 23;
      if ( (qword_151E0C920 & (unsigned __int64)v138) != 0 )
      {
        v142 = *((RenderableComponent **)&v141->_Mypair._Myval2->__vftable + v140);
        v1065 = v135;
        v143 = guard_dispatch_icall_nop(a1: v142);
        v1065 = v135;
        v144 = guard_dispatch_icall_nop(a1: v142);
        if ( (v144 | v143) == 1 )
        {
          if ( v143 != 0 )
          {
            v145 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v146 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v145 != v146 )
            {
              while ( *v145 != v142 )
              {
                if ( ++v145 == v146 )
                  goto LABEL_574;
              }
            }
            if ( v145 != v146 )
            {
              v440 = v144;
              memmove_0(a1: v145, Src: v145 + 1, Size: (char *)v146 - (char *)(v145 + 1));
              v144 = v440;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_574:
          if ( v144 != 0 )
          {
            v441 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v442 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v441 != v442 )
            {
              while ( *v441 != (CustomFrameUpdateComponent *)v142 )
              {
                if ( ++v441 == v442 )
                  goto LABEL_581;
              }
            }
            if ( v441 != v442 )
            {
              memmove_0(a1: v441, Src: v441 + 1, Size: (char *)v442 - (char *)(v441 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_581:
        v443 = *((void (__fastcall ****)(_QWORD, __int64))&v141->_Mypair._Myval2->__vftable + v140);
        *((_QWORD *)&v141->_Mypair._Myval2->__vftable + v140) = v135;
        if ( v443 != nullptr )
          (**v443)(a1: v443, a2: 1);
LABEL_1674:
        v1065 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v135) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v135;
          v897 = ownerControl;
          v898 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v898 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1065 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v898);
          }
          else
          {
            *v898 = (RenderableComponent *)v135;
            ++v897->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1065 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v135) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v135;
          v899 = ownerControl;
          v900 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v900 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1065 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v900);
          }
          else
          {
            *v900 = (CustomFrameUpdateComponent *)v135;
            ++v899->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( dword_151E0C928 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &dword_151E0C928);
          if ( dword_151E0C928 == -1 )
          {
            qword_151E0C920 = 1LL << _InterlockedExchangeAdd64(
                                       (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                       1u);
            Init_thread_footer(pOnce: &dword_151E0C928);
          }
        }
        v901 = ownerControl->mComponentsInUse;
        if ( (qword_151E0C920 & v901) != 0
          && (v902 = ((qword_151E0C920 - 1) & v901) - ((((qword_151E0C920 - 1) & v901) >> 1) & 0x5555555555555555LL),
              v903 = (0x101010101010101LL
                    * (((v902 & 0x3333333333333333LL)
                      + ((v902 >> 2) & 0x3333333333333333LL)
                      + (((v902 & 0x3333333333333333LL) + ((v902 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v904 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v904 > v903) )
        {
          v905 = v904[v903]._Mypair._Myval2;
        }
        else
        {
          v905 = nullptr;
        }
        v1106._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = 0;
        v1069._Mypair._Myval2._Bx._Ptr = "dropdown_name";
        *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 13;
        v906 = (unsigned __int8 *)&defaultValue;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&defaultValue,
          key: (std::string_view *)&v1069,
          defaultValue: (std::string_view *)&v1106);
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
          v906 = *(unsigned __int8 **)&defaultValue.mFileSystem;
        if ( *(_QWORD *)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v908 = *(_QWORD *)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v907 = -2128831035;
            do
            {
              v907 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v907 ^ *v906)) ^ v906[1])) ^ v906[2])) ^ v906[3]))
                          ^ v906[4]))
                        ^ v906[5]))
                      ^ v906[6]))
                    ^ v906[7]);
              v906 += 8;
              v908 -= 8LL;
            }
            while ( v908 != 0 );
          }
          else
          {
            v907 = -2128831035;
          }
          if ( (defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v909 = 0;
            do
              v907 = 16777619 * (v907 ^ v906[v909++]);
            while ( (defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Buf[8] & 7) != v909 );
          }
        }
        else
        {
          v907 = -2128831035;
        }
        LODWORD(v905[1].__vftable) = v907;
        *(_QWORD *)&_Args[0].mIgnored = off_14E8D6F10;
        _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
        __formal._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 0;
        v1076._Mypair._Myval2._Bx._Ptr = "dropdown_content_control";
        *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 24;
        v1105 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&v1076,
          defaultValue: (std::string_view *)&__formal);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1079,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)2);
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v910 = *(void **)&v1079.mIgnored;
          v911 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v911 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v910 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v910, __formal: v911);
        }
        *(_QWORD *)&v1079.mIgnored = off_14E8D6F40;
        v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
        v1073._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 0;
        v1072._Mypair._Myval2._Bx._Ptr = "dropdown_area";
        *(_QWORD *)&v1072._Mypair._Myval2._Bx._Alias[8] = 13;
        v1104 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &Src,
          key: (std::string_view *)&v1072,
          defaultValue: (std::string_view *)&v1073);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&Src,
          setter: nullptr);
        if ( Src._Mypair._Myval2._Myres >= 0x10 )
        {
          v912 = Src._Mypair._Myval2._Bx._Ptr;
          v913 = Src._Mypair._Myval2._Myres + 1;
          if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v913 = Src._Mypair._Myval2._Myres + 40;
            v912 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v912, __formal: v913);
        }
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
        {
          v914 = *(void **)&defaultValue.mFileSystem;
          v915 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
          if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v915 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
            v914 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
          }
          operator delete(block: v914, __formal: v915);
        }
        goto LABEL_1713;
      }
      *(_QWORD *)&_Args[0].mIgnored = v135;
      v348 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v136[23]._Mypair._Myval2 + (unsigned int)(8 * v140));
      v349 = v136[24]._Mypair._Myval2;
      if ( v349 == v136[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v136 + 23,
          _Val: v348);
        v389 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v349 == (StructureFeature *)v348 )
        {
          v349->__vftable = (StructureFeature_vtbl *)v135;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1673:
          ownerControl->mComponentsInUse |= v137;
          goto LABEL_1674;
        }
        v350 = (std::unique_ptr<RuinedPortalFeature> *)&v349[-1].mActiveBlueprintCreateCount;
        v351 = *(StructureFeature_vtbl **)&v349[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v349[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v349->__vftable = v351;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v350 != v348 )
        {
          v352 = v350[-1]._Mypair._Myval2;
          v353 = v350->_Mypair._Myval2;
          v350[-1]._Mypair._Myval2 = nullptr;
          v350->_Mypair._Myval2 = v352;
          if ( v353 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v353->dtr_StructureFeature)(a1: v353, a2: 1);
          --v350;
        }
        v389 = v348->_Mypair._Myval2;
        v348->_Mypair._Myval2 = (RuinedPortalFeature *)v135;
      }
      if ( v389 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v389->dtr_StructureFeature)(a1: v389, a2: 1);
      goto LABEL_1673;
    case 4LL:
      v86 = v1110;
      v87 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateButtonComponent(def: v86, ownerControl: v87);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v86);
      UIControlFactory::_populateFocusComponent(def, ownerControl: (UIControl *)v86);
      UIControlFactory::_populateInputComponent(def, ownerControl: (UIControl *)v86);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: (UIControl *)v86);
      LOBYTE(v88) = 27;
      LOBYTE(v1080) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v88);
      v89 = (UIControl *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                           this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                           a2: 240);
      if ( v89 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0xF0u, alignment: 0);
      v1108 = (RuinedPortalFeature *)v89;
      TextEditComponent::TextEditComponent(owner: v89);
      if ( __TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                         (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                         1u);
          `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v90 = `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId;
      v91 = ownerControl->mComponentsInUse;
      v92 = ((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1))
           - (((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1)) >> 1) & 0x5555555555555555LL))
          & 0x3333333333333333LL;
      v93 = (0x101010101010101LL
           * ((v92
             + ((((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1))
                - (((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1)) >> 1)
                 & 0x5555555555555555LL)) >> 2)
              & 0x3333333333333333LL)
             + ((v92
               + ((((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1))
                  - (((v91 & (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1)) >> 1)
                   & 0x5555555555555555LL)) >> 2)
                & 0x3333333333333333LL)) >> 4))
            & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      p_mComponents = &ownerControl->mComponents;
      v95 = v1108;
      if ( (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId & v91) != 0 )
      {
        v96 = (RenderableComponent *)p_mComponents->_Mypair._Myval2._Myfirst[v93]._Mypair._Myval2;
        v1064 = v1108;
        v97 = guard_dispatch_icall_nop(a1: v96);
        v1064 = v1108;
        v98 = guard_dispatch_icall_nop(a1: v96);
        if ( (v98 | v97) == 1 )
        {
          if ( v97 != 0 )
          {
            v99 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v100 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v99 != v100 )
            {
              while ( *v99 != v96 )
              {
                if ( ++v99 == v100 )
                  goto LABEL_563;
              }
            }
            if ( v99 != v100 )
            {
              v436 = v98;
              memmove_0(a1: v99, Src: v99 + 1, Size: (char *)v100 - (char *)(v99 + 1));
              v98 = v436;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_563:
          if ( v98 != 0 )
          {
            v437 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v438 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v437 != v438 )
            {
              while ( *v437 != (CustomFrameUpdateComponent *)v96 )
              {
                if ( ++v437 == v438 )
                  goto LABEL_570;
              }
            }
            if ( v437 != v438 )
            {
              memmove_0(a1: v437, Src: v437 + 1, Size: (char *)v438 - (char *)(v437 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_570:
        v439 = p_mComponents->_Mypair._Myval2._Myfirst[v93]._Mypair._Myval2;
        v95 = v1108;
        p_mComponents->_Mypair._Myval2._Myfirst[v93]._Mypair._Myval2 = (UIComponent *)v1108;
        if ( v439 != nullptr )
          ((void (__fastcall *)(UIComponent *, __int64))v439->dtr_UIComponent)(a1: v439, a2: 1);
LABEL_1517:
        v1064 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v95) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v1108;
          v836 = ownerControl;
          v837 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v837 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1064 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v837);
          }
          else
          {
            *v837 = (RenderableComponent *)v1108;
            ++v836->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1064 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v1108) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v1108;
          v838 = ownerControl;
          v839 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v839 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1064 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v839);
          }
          else
          {
            *v839 = (CustomFrameUpdateComponent *)v1108;
            ++v838->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                           (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                           1u);
            `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTextEditComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v840 = `uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId;
        v841 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId & v841) != 0
          && (v842 = ((`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1) & v841)
                   - ((((`uicontrol_id<UIComponent,TextEditComponent>'::`2'::id.mBitId - 1) & v841) >> 1)
                    & 0x5555555555555555LL),
              v840 = (0x101010101010101LL
                    * (((v842 & 0x3333333333333333LL)
                      + ((v842 >> 2) & 0x3333333333333333LL)
                      + (((v842 & 0x3333333333333333LL) + ((v842 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v843 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v843 > v840) )
        {
          v844 = v843[v840]._Mypair._Myval2;
        }
        else
        {
          v844 = nullptr;
        }
        if ( def->mDefName._Mypair._Myval2._Bx._Ptr == nullptr
          && Bedrock::Diagnostics::handleAssert(
               msgFormat: "Accessing a null NonOwnerPointer",
               arg: "mControlBlock",
               line: 300,
               file: "D:\\a\\_work\\1\\s\\src\\base\\Core\\include\\Core/Utility/NonOwnerPointer.h",
               a5: "T *Bedrock::NonOwnerPointer<const FontRepository>::_get() const [T = const FontRepository]") )
        {
          MEMORY[0] = -559038242;
        }
        if ( *def->mDefName._Mypair._Myval2._Bx._Ptr == 0
          && Bedrock::Diagnostics::handleAssert(
               msgFormat: "Accessing a dangling NonOwnerPointer after the target object has been deleted",
               arg: "mControlBlock->mIsValid",
               line: 304,
               file: "D:\\a\\_work\\1\\s\\src\\base\\Core\\include\\Core/Utility/NonOwnerPointer.h",
               a5: "T *Bedrock::NonOwnerPointer<const FontRepository>::_get() const [T = const FontRepository]") )
        {
          MEMORY[0] = -559038242;
        }
        v845 = def->mDefName._Mypair._Myval2._Mysize;
        memset(&v1079, 0, 24);
        v846 = *(_QWORD *)(v845 + 224);
        if ( v846 != 0 )
        {
          _InterlockedIncrement((volatile signed __int32 *)(v846 + 8));
          v847 = *(_BYTE **)(v845 + 216);
          v840 = *(_QWORD *)(v845 + 224);
          v848 = (volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr;
          *(_QWORD *)&v1079.mIgnored = v847;
          v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)v840;
          if ( v848 != nullptr )
          {
            if ( _InterlockedDecrement(v848 + 2) == 0 )
            {
              (**(void (__fastcall ***)(volatile signed __int32 *))v848)(a1: v848);
              if ( _InterlockedDecrement(v848 + 3) == 0 )
                (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v848 + 8LL))(a1: v848);
            }
            v847 = *(_BYTE **)&v1079.mIgnored;
          }
        }
        else
        {
          v847 = *(_BYTE **)(v845 + 216);
          *(_OWORD *)&v1079.mIgnored = (unsigned __int64)v847;
        }
        if ( v847 == nullptr
          || (v840 = v845 + 208, *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] = v845 + 208, *v847 == 0) )
        {
          gsl::details::terminate(this: (gsl::details *)v840);
        }
        *(_QWORD *)&_Args[0].mIgnored = &mce::FileWatcherNull::`vftable';
        v849 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                         this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                         a2: 24);
        if ( v849 == nullptr )
          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x18u, alignment: 0);
        *((_QWORD *)v849 + 1) = 0x100000001LL;
        *(_QWORD *)v849 = &std::_Ref_count_obj2<cg::details::WorkToken>::`vftable';
        v849[16] = 1;
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = v849 + 16;
        *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] = v849;
        *(_QWORD *)&_Args[0].mIgnored = &FontHandle::`vftable';
        *(_OWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Mysize = 0;
        v850 = *(_QWORD *)(v845 + 240);
        if ( v850 != 0 )
        {
          _InterlockedIncrement((volatile signed __int32 *)(v850 + 8));
          v851 = *(_QWORD *)(v845 + 240);
        }
        else
        {
          v851 = 0;
        }
        _Args[0].mDefNamespace._Mypair._Myval2._Mysize = *(_QWORD *)(v845 + 232);
        _Args[0].mDefNamespace._Mypair._Myval2._Myres = v851;
        _Args[0].mDefName._Mypair._Myval2._Bx._Ptr = *(char **)(v845 + 248);
        *(std::_String_val<std::_Simple_types<char> >::_Bxty *)((char *)&_Args[0].mDefName._Mypair._Myval2._Bx + 8) = 0;
        v852 = *(_QWORD *)(v845 + 264);
        if ( v852 != 0 )
        {
          _InterlockedIncrement((volatile signed __int32 *)(v852 + 8));
          v853 = *(_QWORD *)(v845 + 264);
        }
        else
        {
          v853 = 0;
        }
        *(_QWORD *)&_Args[0].mDefName._Mypair._Myval2._Bx._Alias[8] = *(_QWORD *)(v845 + 256);
        _Args[0].mDefName._Mypair._Myval2._Mysize = v853;
        _Args[0].mDefName._Mypair._Myval2._Myres = *(_QWORD *)(v845 + 272);
        LOBYTE(_Args[0].mBaseVal) = *(_BYTE *)(v845 + 280);
        if ( &v844[2] != (UIComponent *)_Args )
        {
          v854 = (volatile signed __int32 *)v844[4].__vftable;
          *(_OWORD *)&v844[3].mOwner = 0;
          if ( v854 != nullptr && _InterlockedDecrement(v854 + 2) == 0 )
          {
            (**(void (__fastcall ***)(volatile signed __int32 *))v854)(a1: v854);
            if ( _InterlockedDecrement(v854 + 3) == 0 )
              (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v854 + 8LL))(a1: v854);
          }
          v844[4].mOwner = nullptr;
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Myres != 0 )
          {
            _InterlockedIncrement((volatile signed __int32 *)(_Args[0].mDefNamespace._Mypair._Myval2._Myres + 8));
            v855 = _Args[0].mDefNamespace._Mypair._Myval2._Myres;
          }
          else
          {
            v855 = 0;
          }
          v844[3].mOwner = (UIControl *)_Args[0].mDefNamespace._Mypair._Myval2._Mysize;
          v856 = (volatile signed __int32 *)v844[4].__vftable;
          v844[4].__vftable = (UIComponent_vtbl *)v855;
          if ( v856 != nullptr && _InterlockedDecrement(v856 + 2) == 0 )
          {
            (**(void (__fastcall ***)(volatile signed __int32 *))v856)(a1: v856);
            if ( _InterlockedDecrement(v856 + 3) == 0 )
              (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v856 + 8LL))(a1: v856);
          }
          v844[4].mOwner = (UIControl *)_Args[0].mDefName._Mypair._Myval2._Bx._Ptr;
          v853 = _Args[0].mDefName._Mypair._Myval2._Mysize;
        }
        if ( v853 != 0 )
        {
          _InterlockedIncrement((volatile signed __int32 *)(v853 + 8));
          v857 = _Args[0].mDefName._Mypair._Myval2._Mysize;
        }
        else
        {
          v857 = 0;
        }
        v844[5].__vftable = *(UIComponent_vtbl **)&_Args[0].mDefName._Mypair._Myval2._Bx._Alias[8];
        mOwner = (volatile signed __int32 *)v844[5].mOwner;
        v844[5].mOwner = (UIControl *)v857;
        if ( mOwner != nullptr && _InterlockedDecrement(mOwner + 2) == 0 )
        {
          (**(void (__fastcall ***)(volatile signed __int32 *))mOwner)(a1: mOwner);
          if ( _InterlockedDecrement(mOwner + 3) == 0 )
            (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)mOwner + 8LL))(a1: mOwner);
        }
        LOBYTE(v844[6].mOwner) = _Args[0].mBaseVal;
        v844[6].__vftable = (UIComponent_vtbl *)_Args[0].mDefName._Mypair._Myval2._Myres;
        FontHandle::~FontHandle(this: (FontHandle *)_Args);
        v859 = (volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr;
        *(_OWORD *)&v1079.mIgnored = 0;
        if ( v859 != nullptr )
        {
          if ( _InterlockedDecrement(v859 + 2) == 0 )
          {
            (**(void (__fastcall ***)(volatile signed __int32 *))v859)(a1: v859);
            if ( _InterlockedDecrement(v859 + 3) == 0 )
              (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v859 + 8LL))(a1: v859);
          }
          v860 = (volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr;
          *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] = 0;
          if ( v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr != nullptr
            && _InterlockedDecrement((volatile signed __int32 *)v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr + 2) == 0 )
          {
            (**(void (__fastcall ***)(volatile signed __int32 *))v860)(a1: v860);
            if ( _InterlockedDecrement(v860 + 3) == 0 )
              (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v860 + 8LL))(a1: v860);
          }
        }
        v1076._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 0;
        v1073._Mypair._Myval2._Bx._Ptr = "text_box_name";
        *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 13;
        v861 = &v1106;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &v1106,
          key: (std::string_view *)&v1073,
          defaultValue: (std::string_view *)&v1076);
        if ( v1106._Mypair._Myval2._Myres >= 0x10 )
          v861 = (std::string *)v1106._Mypair._Myval2._Bx._Ptr;
        if ( v1106._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1106._Mypair._Myval2._Mysize >= 8 )
          {
            v863 = v1106._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v862 = -2128831035;
            do
            {
              v862 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v862 ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[7]);
              v861 = (std::string *)((char *)v861 + 8);
              v863 -= 8LL;
            }
            while ( v863 != 0 );
          }
          else
          {
            v862 = -2128831035;
          }
          if ( (v1106._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v864 = 0;
            do
              v862 = 16777619 * (v862 ^ (unsigned __int8)v861->_Mypair._Myval2._Bx._Buf[v864++]);
            while ( (v1106._Mypair._Myval2._Mysize & 7) != v864 );
          }
        }
        else
        {
          v862 = -2128831035;
        }
        LODWORD(v844[14].mOwner) = v862;
        v1072._Mypair._Myval2._Bx = (std::_String_val<std::_Simple_types<char> >::_Bxty)(unsigned __int64)u;
        v1068._Mypair._Myval2._Bx._Ptr = "text_edit_box_grid_collection_name";
        *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 34;
        v865 = &v1079;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&v1068,
          defaultValue: (std::string_view *)&v1072);
        v867 = (UIControl *)&v844[12].mOwner;
        if ( &v844[12].mOwner != (UIControl **)&v1079 )
        {
          v868 = *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
            v865 = *(UIResolvedDef **)&v1079.mIgnored;
          v869 = (unsigned __int64)v844[14].__vftable;
          if ( *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v869 )
          {
            if ( v869 >= 0x10 )
              v867 = v844[12].mOwner;
            v844[13].mOwner = *(UIControl **)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
            memmove_0(a1: v867, Src: v865, Size: v868);
            *((_BYTE *)&v867->_Wptr._Ptr + v868) = 0;
          }
          else
          {
            ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
              this: (std::string *)&v844[12].mOwner,
              _New_size: *(const unsigned __int64 *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8],
              _Fn: v866,
              _Args: (const char *)&v865->mIgnored);
          }
        }
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v870 = *(void **)&v1079.mIgnored;
          v871 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v871 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v870 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v870, __formal: v871);
        }
        *(_QWORD *)&v1079.mIgnored = "constrain_to_rect";
        v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)17;
        v872 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1079, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v872) && !Json::Value::isBool(this: v872) )
          Json::Value::isIntegral(this: v872);
        v873 = Json::Value::isIntegral(this: v872) && Json::Value::asBool(this: v872, defaultValue: false);
        BYTE4(v844[1].__vftable) = v873;
        *(_QWORD *)&v1079.mIgnored = "enabled_newline";
        v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)15;
        v874 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1079, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v874) && !Json::Value::isBool(this: v874) )
          Json::Value::isIntegral(this: v874);
        v875 = Json::Value::isIntegral(this: v874) && Json::Value::asBool(this: v874, defaultValue: false);
        BYTE5(v844[1].__vftable) = v875;
        v1048._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 0;
        v1049._Mypair._Myval2._Bx._Ptr = "text_type";
        *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 9;
        v876 = &v1069;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &v1069,
          key: (std::string_view *)&v1049,
          defaultValue: (std::string_view *)&v1048);
        if ( v1069._Mypair._Myval2._Myres >= 0x10 )
          v876 = (std::string *)v1069._Mypair._Myval2._Bx._Ptr;
        if ( v1069._Mypair._Myval2._Mysize == 11 )
        {
          if ( ((__int64)v876->_Mypair._Myval2._Bx._Ptr ^ 0x68437265626D754ELL
              | *(_QWORD *)&v876->_Mypair._Myval2._Bx._Alias[3] ^ 0x7372616843726562LL) == 0 )
          {
            v877 = 2;
            goto LABEL_1628;
          }
        }
        else
        {
          if ( v1069._Mypair._Myval2._Mysize != 15 )
          {
            if ( v1069._Mypair._Myval2._Mysize != 13
              || ((__int64)v876->_Mypair._Myval2._Bx._Ptr ^ 0x6465646E65747845LL
                | *(_QWORD *)&v876->_Mypair._Myval2._Bx._Alias[5] ^ 0x4949435341646564LL) != 0 )
            {
              goto LABEL_1629;
            }
            v877 = 0;
            goto LABEL_1628;
          }
          if ( ((__int64)v876->_Mypair._Myval2._Bx._Ptr ^ 0x696669746E656449LL
              | *(_QWORD *)&v876->_Mypair._Myval2._Bx._Alias[7] ^ 0x7372616843726569LL) == 0 )
          {
            v877 = 1;
LABEL_1628:
            LODWORD(v844[1].mOwner) = v877;
          }
        }
LABEL_1629:
        *(_QWORD *)&v1079.mIgnored = "max_length";
        v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)10;
        v878 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1079, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v878) )
          Json::Value::isNumeric(this: v878);
        isInt = Json::Value::isInt(this: v878);
        v880 = 0;
        if ( isInt )
          v880 = Json::Value::asInt(this: v878, defaultValue: 0);
        LODWORD(v844[1].__vftable) = v880;
        *(_QWORD *)&v1079.mIgnored = off_14E8D7270;
        v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
        v1046._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1046._Mypair._Myval2._Bx._Alias[8] = 0;
        v1071._Mydata = "virtual_keyboard_buffer_control";
        v1071._Mysize = 31;
        v1103 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&defaultValue,
          key: &v1071,
          defaultValue: (std::string_view *)&v1046);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&defaultValue,
          setter: nullptr);
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
        {
          v881 = *(void **)&defaultValue.mFileSystem;
          v882 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
          if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v882 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
            v881 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
          }
          operator delete(block: v881, __formal: v882);
        }
        *(_QWORD *)&defaultValue.mFileSystem = off_14E8D72A0;
        v1078 = &defaultValue;
        v1041._Mydata = u;
        v1041._Mysize = 0;
        v1042._Mydata = "text_control";
        v1042._Mysize = 12;
        v1102 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &Src, key: &v1042, defaultValue: &v1041);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&Src,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( Src._Mypair._Myval2._Myres >= 0x10 )
        {
          v883 = Src._Mypair._Myval2._Bx._Ptr;
          v884 = Src._Mypair._Myval2._Myres + 1;
          if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v884 = Src._Mypair._Myval2._Myres + 40;
            v883 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v883, __formal: v884);
        }
        Src._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D72D0;
        p_Src = &Src;
        v1043._Mydata = u;
        v1043._Mysize = 0;
        v1044._Mydata = "place_holder_control";
        v1044._Mysize = 20;
        v1101 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &__formal, key: &v1044, defaultValue: &v1043);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&__formal,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( __formal._Mypair._Myval2._Myres >= 0x10 )
        {
          v885 = __formal._Mypair._Myval2._Bx._Ptr;
          v886 = __formal._Mypair._Myval2._Myres + 1;
          if ( __formal._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&__formal._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)__formal._Mypair._Myval2._Bx._Ptr - 1)
                                                                    - 8] >= 0x20 )
              goto LABEL_1922;
            v886 = __formal._Mypair._Myval2._Myres + 40;
            v885 = *((char **)__formal._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v885, __formal: v886);
        }
        __formal._Mypair._Myval2._Bx._Ptr = "can_be_deselected";
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 17;
        v887 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&__formal, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v887) && !Json::Value::isBool(this: v887) )
          Json::Value::isIntegral(this: v887);
        isIntegral = Json::Value::isIntegral(this: v887);
        v889 = true;
        if ( isIntegral )
          v889 = Json::Value::asBool(this: v887, defaultValue: false);
        BYTE4(v844[14].mOwner) = v889;
        __formal._Mypair._Myval2._Bx._Ptr = "always_listening";
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 16;
        v890 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&__formal, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v890) && !Json::Value::isBool(this: v890) )
          Json::Value::isIntegral(this: v890);
        v891 = Json::Value::isIntegral(this: v890) && Json::Value::asBool(this: v890, defaultValue: false);
        HIBYTE(v844[14].mOwner) = v891;
        v892 = v844->mOwner;
        if ( (*((_BYTE *)v892 + 25) & 0x10) == 0 )
          v892->mControlScreenAction->markTextEditAlwaysListeningChanged(this: v892->mControlScreenAction);
        v1045._Mydata = "place_holder_text_hover_color";
        v1045._Mysize = 29;
        UIResolvedDef::getAsColor(
          this: v1110,
          result: (mce::Color *)&__formal,
          key: &v1045,
          defaultValue: &Palette::WHITE);
        v844[7] = (UIComponent)_mm_loadu_si128((const __m128i *)&__formal);
        if ( v1069._Mypair._Myval2._Myres >= 0x10 )
        {
          v893 = v1069._Mypair._Myval2._Bx._Ptr;
          v894 = v1069._Mypair._Myval2._Myres + 1;
          if ( v1069._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1069._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1069._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v894 = v1069._Mypair._Myval2._Myres + 40;
            v893 = *((char **)v1069._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v893, __formal: v894);
        }
        if ( v1106._Mypair._Myval2._Myres >= 0x10 )
        {
          v895 = v1106._Mypair._Myval2._Bx._Ptr;
          v896 = v1106._Mypair._Myval2._Myres + 1;
          if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v896 = v1106._Mypair._Myval2._Myres + 40;
            v895 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v895, __formal: v896);
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1080);
        v43 = ownerControl;
        UIControlFactory::_populateTextToSpeechComponent(def: v1110, ownerControl, controlPriorityDefault: 1000);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v1108;
      v342 = (std::unique_ptr<RuinedPortalFeature> *)((char *)ownerControl->mComponents._Mypair._Myval2._Myfirst
                                                    + (unsigned int)(8 * v93));
      v343 = ownerControl->mComponents._Mypair._Myval2._Mylast;
      if ( v343 == ownerControl->mComponents._Mypair._Myval2._Myend )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: (std::unique_ptr<StructureFeature> *)&ownerControl->mComponents,
          _Val: v342);
        v388 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v343 == (std::unique_ptr<UIComponent> *)v342 )
        {
          v343->_Mypair._Myval2 = (UIComponent *)v1108;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1516:
          ownerControl->mComponentsInUse |= v90;
          goto LABEL_1517;
        }
        v344 = (std::unique_ptr<RuinedPortalFeature> *)&v343[-1];
        v345 = v343[-1]._Mypair._Myval2;
        v343[-1]._Mypair._Myval2 = nullptr;
        v343->_Mypair._Myval2 = v345;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v344 != v342 )
        {
          v346 = v344[-1]._Mypair._Myval2;
          v347 = v344->_Mypair._Myval2;
          v344[-1]._Mypair._Myval2 = nullptr;
          v344->_Mypair._Myval2 = v346;
          if ( v347 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v347->dtr_StructureFeature)(a1: v347, a2: 1);
          --v344;
        }
        v388 = v342->_Mypair._Myval2;
        v342->_Mypair._Myval2 = v95;
      }
      if ( v388 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v388->dtr_StructureFeature)(a1: v388, a2: 1);
      goto LABEL_1516;
    case 5LL:
      v192 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v192);
      goto LABEL_1734;
    case 6LL:
      v222 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v222);
      UIControlFactory::_populateGridComponent(
        context: (const UIControlFactoryContext *)def,
        def: resolvedDef,
        ownerControl: v222);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v222);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v222);
      goto LABEL_1734;
    case 7LL:
      v147 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v147);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v147);
      UIControlFactory::_populateSpriteComponent(def, ownerControl: v147);
      goto LABEL_1734;
    case 8LL:
      v239 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v239);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v239);
      UIControlFactory::_populateInputComponent(def, ownerControl: v239);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v239);
      UIControlFactory::_populateGestureComponent(def: (const UIResolvedDef *)v239, ownerControl: v43);
      UIControlFactory::_populateSoundComponent(def, ownerControl: v239, a3: (bool)v43);
      UIControlFactory::_populateTextToSpeechComponent(
        def: (const UIResolvedDef *)v239,
        ownerControl: v43,
        controlPriorityDefault: 1000);
      goto LABEL_1734;
    case 9LL:
      v117 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v117);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v117);
      UIControlFactory::_populateTextComponent(def, ownerControl: v117);
      UIControlFactory::_populateTextToSpeechComponent(
        def: (const UIResolvedDef *)v117,
        ownerControl: v43,
        controlPriorityDefault: 0);
      goto LABEL_1734;
    case 10LL:
      v238 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v238);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v238);
      goto LABEL_1734;
    case 11LL:
      ownerControl->mZOrder = -1;
      v72 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v72);
      UIControlFactory::_populateInputComponent(def, ownerControl: v72);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v72);
      LOBYTE(v73) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v73);
      v74 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                      a2: 40);
      if ( v74 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x28u, alignment: 0);
      v75 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v74 + 1) = ownerControl;
      *(_QWORD *)v74 = &off_14E8D5D80;
      *((_QWORD *)v74 + 2) = &off_14E8D5E00;
      *((_WORD *)v74 + 12) = 532;
      v74[26] = 2;
      *(_QWORD *)(v74 + 28) = 0;
      if ( __TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                      (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                      1u);
          `uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v76 = `uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId;
      v77 = v75[22]._Mypair._Myval2;
      v78 = (((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1))
           - ((((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1)) >> 1)
            & 0x5555555555555555LL))
          & 0x3333333333333333LL;
      v79 = (0x101010101010101LL
           * ((v78
             + (((((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1))
                - ((((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1)) >> 1)
                 & 0x5555555555555555LL)) >> 2)
              & 0x3333333333333333LL)
             + ((v78
               + (((((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1))
                  - ((((unsigned __int64)v77 & (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1)) >> 1)
                   & 0x5555555555555555LL)) >> 2)
                & 0x3333333333333333LL)) >> 4))
            & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v80 = v75 + 23;
      if ( (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId & (unsigned __int64)v77) != 0 )
      {
        v81 = *((RenderableComponent **)&v80->_Mypair._Myval2->__vftable + v79);
        v1063 = v74;
        v82 = guard_dispatch_icall_nop(a1: v81);
        v1063 = v74;
        v83 = guard_dispatch_icall_nop(a1: v81);
        if ( (v83 | v82) == 1 )
        {
          if ( v82 != 0 )
          {
            v84 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v85 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v84 != v85 )
            {
              while ( *v84 != v81 )
              {
                if ( ++v84 == v85 )
                  goto LABEL_486;
              }
            }
            if ( v84 != v85 )
            {
              v408 = v83;
              memmove_0(a1: v84, Src: v84 + 1, Size: (char *)v85 - (char *)(v84 + 1));
              v83 = v408;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_486:
          if ( v83 != 0 )
          {
            v409 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v410 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v409 != v410 )
            {
              while ( *v409 != (CustomFrameUpdateComponent *)v81 )
              {
                if ( ++v409 == v410 )
                  goto LABEL_493;
              }
            }
            if ( v409 != v410 )
            {
              memmove_0(a1: v409, Src: v409 + 1, Size: (char *)v410 - (char *)(v409 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_493:
        v411 = *((void (__fastcall ****)(_QWORD, __int64))&v80->_Mypair._Myval2->__vftable + v79);
        *((_QWORD *)&v80->_Mypair._Myval2->__vftable + v79) = v74;
        if ( v411 != nullptr )
          (**v411)(a1: v411, a2: 1);
LABEL_1046:
        v1063 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v74) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v74;
          v639 = ownerControl;
          v640 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v640 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1063 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v640);
          }
          else
          {
            *v640 = (RenderableComponent *)v74;
            ++v639->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1063 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v74) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v74;
          v641 = ownerControl;
          v642 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v642 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1063 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v642);
          }
          else
          {
            *v642 = (CustomFrameUpdateComponent *)v74;
            ++v641->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                        (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                        1u);
            `uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScreenSettings____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v643 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId & v643) != 0
          && (v644 = ((`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1) & v643)
                   - ((((`uicontrol_id<UIComponent,ScreenSettings>'::`2'::id.mBitId - 1) & v643) >> 1)
                    & 0x5555555555555555LL),
              v645 = (0x101010101010101LL
                    * (((v644 & 0x3333333333333333LL)
                      + ((v644 >> 2) & 0x3333333333333333LL)
                      + (((v644 & 0x3333333333333333LL) + ((v644 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v646 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v646 > v645) )
        {
          v647 = v646[v645]._Mypair._Myval2;
        }
        else
        {
          v647 = nullptr;
        }
        *(_QWORD *)&_Args[0].mIgnored = "screen_not_flushable";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)20;
        v648 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v648) && !Json::Value::isBool(this: v648) )
          Json::Value::isIntegral(this: v648);
        v649 = Json::Value::isIntegral(this: v648) && Json::Value::asBool(this: v648, defaultValue: false);
        LOBYTE(v647[1].mOwner) = v649 | (__int64)v647[1].mOwner & 0xFE;
        *(_QWORD *)&_Args[0].mIgnored = "always_accepts_input";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)20;
        v650 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v650) && !Json::Value::isBool(this: v650) )
          Json::Value::isIntegral(this: v650);
        if ( Json::Value::isIntegral(this: v650) )
          v651 = 2 * Json::Value::asBool(this: v650, defaultValue: false);
        else
          v651 = 0;
        LOBYTE(v647[1].mOwner) = v651 | (__int64)v647[1].mOwner & 0xFD;
        *(_QWORD *)&_Args[0].mIgnored = "render_game_behind";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)18;
        v652 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v652) && !Json::Value::isBool(this: v652) )
          Json::Value::isIntegral(this: v652);
        if ( Json::Value::isIntegral(this: v652) )
          v653 = 4 * Json::Value::asBool(this: v652, defaultValue: false);
        else
          v653 = 4;
        LOBYTE(v647[1].mOwner) = v653 | (__int64)v647[1].mOwner & 0xFB;
        *(_QWORD *)&_Args[0].mIgnored = "absorbs_input";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)13;
        v654 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v654) && !Json::Value::isBool(this: v654) )
          Json::Value::isIntegral(this: v654);
        if ( Json::Value::isIntegral(this: v654) )
          v655 = 8 * Json::Value::asBool(this: v654, defaultValue: false);
        else
          v655 = 8;
        LOBYTE(v647[1].mOwner) = v655 | (__int64)v647[1].mOwner & 0xF7;
        *(_QWORD *)&_Args[0].mIgnored = "is_showing_menu";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)15;
        v656 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v656) && !Json::Value::isBool(this: v656) )
          Json::Value::isIntegral(this: v656);
        if ( Json::Value::isIntegral(this: v656) )
          v657 = 16 * Json::Value::asBool(this: v656, defaultValue: false);
        else
          v657 = 16;
        LOBYTE(v647[1].mOwner) = v657 | (__int64)v647[1].mOwner & 0xEF;
        *(_QWORD *)&_Args[0].mIgnored = "is_modal";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)8;
        v658 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v658) && !Json::Value::isBool(this: v658) )
          Json::Value::isIntegral(this: v658);
        if ( Json::Value::isIntegral(this: v658) )
          v659 = 32 * Json::Value::asBool(this: v658, defaultValue: false);
        else
          v659 = 0;
        LOBYTE(v647[1].mOwner) = v659 | (__int64)v647[1].mOwner & 0xDF;
        *(_QWORD *)&_Args[0].mIgnored = "should_steal_mouse";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)18;
        v660 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v660) && !Json::Value::isBool(this: v660) )
          Json::Value::isIntegral(this: v660);
        if ( Json::Value::isIntegral(this: v660) )
          v661 = Json::Value::asBool(this: v660, defaultValue: false) << 6;
        else
          v661 = 0;
        LOBYTE(v647[1].mOwner) = v661 | (__int64)v647[1].mOwner & 0xBF;
        *(_QWORD *)&_Args[0].mIgnored = "low_frequency_rendering";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)23;
        v662 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v662) && !Json::Value::isBool(this: v662) )
          Json::Value::isIntegral(this: v662);
        if ( Json::Value::isIntegral(this: v662) )
          v663 = 4 * Json::Value::asBool(this: v662, defaultValue: false);
        else
          v663 = 0;
        BYTE1(v647[1].mOwner) = v663 | BYTE1(v647[1].mOwner) & 0xFB;
        *(_QWORD *)&_Args[0].mIgnored = "screen_draws_last";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)17;
        v664 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v664) && !Json::Value::isBool(this: v664) )
          Json::Value::isIntegral(this: v664);
        if ( Json::Value::isIntegral(this: v664) )
          v665 = Json::Value::asBool(this: v664, defaultValue: false) << 7;
        else
          v665 = 0;
        LOBYTE(v647[1].mOwner) = v665 | (__int64)v647[1].mOwner & 0x7F;
        *(_QWORD *)&_Args[0].mIgnored = "force_render_below";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)18;
        v666 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v666) && !Json::Value::isBool(this: v666) )
          Json::Value::isIntegral(this: v666);
        v667 = Json::Value::isIntegral(this: v666) && Json::Value::asBool(this: v666, defaultValue: false);
        BYTE1(v647[1].mOwner) = v667 | BYTE1(v647[1].mOwner) & 0xFE;
        *(_QWORD *)&_Args[0].mIgnored = "send_telemetry";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)14;
        v668 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v668) && !Json::Value::isBool(this: v668) )
          Json::Value::isIntegral(this: v668);
        if ( Json::Value::isIntegral(this: v668) )
          v669 = 2 * Json::Value::asBool(this: v668, defaultValue: false);
        else
          v669 = 2;
        BYTE1(v647[1].mOwner) = v669 | BYTE1(v647[1].mOwner) & 0xFD;
        *(_QWORD *)&_Args[0].mIgnored = "close_on_player_hurt";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)20;
        v670 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v670) && !Json::Value::isBool(this: v670) )
          Json::Value::isIntegral(this: v670);
        if ( Json::Value::isIntegral(this: v670) )
          v671 = 8 * Json::Value::asBool(this: v670, defaultValue: false);
        else
          v671 = 0;
        BYTE1(v647[1].mOwner) = v671 | BYTE1(v647[1].mOwner) & 0xF7;
        *(_QWORD *)&_Args[0].mIgnored = "use_custom_pocket_toast";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)23;
        v672 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v672) && !Json::Value::isBool(this: v672) )
          Json::Value::isIntegral(this: v672);
        if ( Json::Value::isIntegral(this: v672) )
          v673 = 16 * Json::Value::asBool(this: v672, defaultValue: false);
        else
          v673 = 0;
        BYTE1(v647[1].mOwner) = v673 | BYTE1(v647[1].mOwner) & 0xEF;
        *(_QWORD *)&_Args[0].mIgnored = "cache_screen";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v674 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v674) && !Json::Value::isBool(this: v674) )
          Json::Value::isIntegral(this: v674);
        if ( Json::Value::isIntegral(this: v674) )
          v675 = 32 * Json::Value::asBool(this: v674, defaultValue: false);
        else
          v675 = 0;
        BYTE1(v647[1].mOwner) = v675 | BYTE1(v647[1].mOwner) & 0xDF;
        *(_QWORD *)&_Args[0].mIgnored = "gamepad_cursor";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)14;
        v676 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v676) && !Json::Value::isBool(this: v676) )
          Json::Value::isIntegral(this: v676);
        if ( Json::Value::isIntegral(this: v676) )
          v677 = Json::Value::asBool(this: v676, defaultValue: false) << 6;
        else
          v677 = 0;
        BYTE1(v647[1].mOwner) = v677 | BYTE1(v647[1].mOwner) & 0xBF;
        *(_QWORD *)&_Args[0].mIgnored = "gamepad_cursor_deflection_mode";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)30;
        v678 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v678) && !Json::Value::isBool(this: v678) )
          Json::Value::isIntegral(this: v678);
        if ( Json::Value::isIntegral(this: v678) )
          v679 = Json::Value::asBool(this: v678, defaultValue: false) << 7;
        else
          v679 = 0;
        BYTE1(v647[1].mOwner) = v679 | BYTE1(v647[1].mOwner) & 0x7F;
        *(_QWORD *)&_Args[0].mIgnored = "vertical_scroll_delta";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)21;
        v680 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v680) )
          Json::Value::isNumeric(this: v680);
        if ( Json::Value::isNumeric(this: v680) )
          *(float *)v681.m128i_i32 = Json::Value::asFloat(this: v680, defaultValue: 0.0);
        else
          v681 = _mm_cvtsi32_si128(0x41A00000u);
        HIDWORD(v647[1].mOwner) = _mm_cvtsi128_si32(v681);
        *(_QWORD *)&_Args[0].mIgnored = "load_screen_immediately";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)23;
        v682 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v682) && !Json::Value::isBool(this: v682) )
          Json::Value::isIntegral(this: v682);
        v683 = Json::Value::isIntegral(this: v682) && Json::Value::asBool(this: v682, defaultValue: false);
        BYTE2(v647[1].mOwner) = v683 | BYTE2(v647[1].mOwner) & 0xFE;
        *(_QWORD *)&_Args[0].mIgnored = "render_only_when_topmost";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)24;
        v684 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v684) && !Json::Value::isBool(this: v684) )
          Json::Value::isIntegral(this: v684);
        if ( Json::Value::isIntegral(this: v684) )
          v685 = 2 * Json::Value::asBool(this: v684, defaultValue: false);
        else
          v685 = 2;
        BYTE2(v647[1].mOwner) = v685 | BYTE2(v647[1].mOwner) & 0xFD;
        *(_QWORD *)&_Args[0].mIgnored = "should_be_skipped_during_automation";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)35;
        v686 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v686) && !Json::Value::isBool(this: v686) )
          Json::Value::isIntegral(this: v686);
        if ( Json::Value::isIntegral(this: v686) )
          v687 = 4 * Json::Value::asBool(this: v686, defaultValue: false);
        else
          v687 = 0;
        BYTE2(v647[1].mOwner) = v687 | BYTE2(v647[1].mOwner) & 0xFB;
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1108);
        v43 = ownerControl;
        UIControlFactory::_populateSoundComponent(def, ownerControl: (UIControl *)v1110, a3: (bool)ownerControl);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v74;
      v300 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v75[23]._Mypair._Myval2 + (unsigned int)(8 * v79));
      v301 = v75[24]._Mypair._Myval2;
      if ( v301 == v75[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v75 + 23,
          _Val: v300);
        v381 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v301 == (StructureFeature *)v300 )
        {
          v301->__vftable = (StructureFeature_vtbl *)v74;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1045:
          ownerControl->mComponentsInUse |= v76;
          goto LABEL_1046;
        }
        v302 = (std::unique_ptr<RuinedPortalFeature> *)&v301[-1].mActiveBlueprintCreateCount;
        v303 = *(StructureFeature_vtbl **)&v301[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v301[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v301->__vftable = v303;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v302 != v300 )
        {
          v304 = v302[-1]._Mypair._Myval2;
          v305 = v302->_Mypair._Myval2;
          v302[-1]._Mypair._Myval2 = nullptr;
          v302->_Mypair._Myval2 = v304;
          if ( v305 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v305->dtr_StructureFeature)(a1: v305, a2: 1);
          --v302;
        }
        v381 = v300->_Mypair._Myval2;
        v300->_Mypair._Myval2 = (RuinedPortalFeature *)v74;
      }
      if ( v381 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v381->dtr_StructureFeature)(a1: v381, a2: 1);
      goto LABEL_1045;
    case 12LL:
      v101 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateInputComponent(def, ownerControl: v101);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v101);
      LOBYTE(v102) = 27;
      LOBYTE(v1110) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v102);
      v103 = (UIResolvedDef *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                a2: 32);
      if ( v103 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
      v104 = ownerControl;
      v103->mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)ownerControl;
      *(_QWORD *)&v103->mIgnored = &off_14E8D5FB0;
      def = v103;
      *(std::_String_val<std::_Simple_types<char> >::_Bxty *)((char *)&v103->mDefNamespace._Mypair._Myval2._Bx + 8) = 0;
      PropertyBag = (UIPropertyBag *)UIControl::getPropertyBag(this: v104);
      v1079.mIgnored = true;
      *(_QWORD *)&_Args[0].mIgnored = "#is_scroll_bar_box";
      _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)18;
      UIPropertyBag::set<bool>(this: PropertyBag, key: (std::string_view *)_Args, value: &v1079.mIgnored);
      if ( dword_151E0C948 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C948);
        if ( dword_151E0C948 == -1 )
        {
          qword_151E0C940 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C948);
        }
      }
      v106 = qword_151E0C940;
      v107 = ownerControl->mComponentsInUse;
      v108 = ((v107 & (qword_151E0C940 - 1)) - (((v107 & (qword_151E0C940 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v109 = (0x101010101010101LL
            * ((v108
              + ((((v107 & (qword_151E0C940 - 1)) - (((v107 & (qword_151E0C940 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v108
                + ((((v107 & (qword_151E0C940 - 1)) - (((v107 & (qword_151E0C940 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v110 = &ownerControl->mComponents;
      v111 = def;
      if ( (qword_151E0C940 & v107) != 0 )
      {
        v112 = (RenderableComponent *)v110->_Mypair._Myval2._Myfirst[v109]._Mypair._Myval2;
        v1061 = def;
        v113 = guard_dispatch_icall_nop(a1: v112);
        v1061 = v111;
        v114 = guard_dispatch_icall_nop(a1: v112);
        if ( (v114 | v113) == 1 )
        {
          if ( v113 != 0 )
          {
            v115 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v116 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v115 != v116 )
            {
              while ( *v115 != v112 )
              {
                if ( ++v115 == v116 )
                  goto LABEL_530;
              }
            }
            if ( v115 != v116 )
            {
              v424 = v114;
              memmove_0(a1: v115, Src: v115 + 1, Size: (char *)v116 - (char *)(v115 + 1));
              v114 = v424;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_530:
          if ( v114 != 0 )
          {
            v425 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v426 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v425 != v426 )
            {
              while ( *v425 != (CustomFrameUpdateComponent *)v112 )
              {
                if ( ++v425 == v426 )
                  goto LABEL_537;
              }
            }
            if ( v425 != v426 )
            {
              memmove_0(a1: v425, Src: v425 + 1, Size: (char *)v426 - (char *)(v425 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_537:
        v427 = v110->_Mypair._Myval2._Myfirst[v109]._Mypair._Myval2;
        v110->_Mypair._Myval2._Myfirst[v109]._Mypair._Myval2 = (UIComponent *)v111;
        if ( v427 != nullptr )
          ((void (__fastcall *)(UIComponent *, __int64))v427->dtr_UIComponent)(a1: v427, a2: 1);
LABEL_1390:
        v1061 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v111) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v111;
          v773 = ownerControl;
          v774 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v774 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1061 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v774);
          }
          else
          {
            *v774 = (RenderableComponent *)v111;
            ++v773->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1061 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v111) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v111;
          v775 = ownerControl;
          v776 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v776 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1061 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v776);
          }
          else
          {
            *v776 = (CustomFrameUpdateComponent *)v111;
            ++v775->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1110);
        v43 = ownerControl;
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = def;
      v324 = (std::unique_ptr<RuinedPortalFeature> *)((char *)ownerControl->mComponents._Mypair._Myval2._Myfirst
                                                    + (unsigned int)(8 * v109));
      v325 = ownerControl->mComponents._Mypair._Myval2._Mylast;
      if ( v325 == ownerControl->mComponents._Mypair._Myval2._Myend )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: (std::unique_ptr<StructureFeature> *)&ownerControl->mComponents,
          _Val: v324);
        v385 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v325 == (std::unique_ptr<UIComponent> *)v324 )
        {
          v325->_Mypair._Myval2 = (UIComponent *)def;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1389:
          ownerControl->mComponentsInUse |= v106;
          goto LABEL_1390;
        }
        v326 = (std::unique_ptr<RuinedPortalFeature> *)&v325[-1];
        v327 = v325[-1]._Mypair._Myval2;
        v325[-1]._Mypair._Myval2 = nullptr;
        v325->_Mypair._Myval2 = v327;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v326 != v324 )
        {
          v328 = v326[-1]._Mypair._Myval2;
          v329 = v326->_Mypair._Myval2;
          v326[-1]._Mypair._Myval2 = nullptr;
          v326->_Mypair._Myval2 = v328;
          if ( v329 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v329->dtr_StructureFeature)(a1: v329, a2: 1);
          --v326;
        }
        v385 = v324->_Mypair._Myval2;
        v324->_Mypair._Myval2 = (RuinedPortalFeature *)v111;
      }
      if ( v385 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v385->dtr_StructureFeature)(a1: v385, a2: 1);
      goto LABEL_1389;
    case 13LL:
      v208 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v208);
      UIControlFactory::_populateInputComponent(def, ownerControl: v208);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v208);
      LOBYTE(v209) = 27;
      LOBYTE(def) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                      a2: (Memory::MemoryCategory)v209);
      v210 = (RenderableComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                      a2: 32);
      if ( v210 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
      v211 = (std::unique_ptr<StructureFeature> *)ownerControl;
      v210->mOwner = ownerControl;
      v210->__vftable = (RenderableComponent_vtbl *)&off_14E8D5EB0;
      *(_OWORD *)&v210->mSupportsLayoutOverride = 0;
      if ( dword_151E0C938 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C938);
        if ( dword_151E0C938 == -1 )
        {
          qword_151E0C930 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C938);
        }
      }
      v212 = qword_151E0C930;
      v213 = v211[22]._Mypair._Myval2;
      v214 = (((unsigned __int64)v213 & (qword_151E0C930 - 1))
            - ((((unsigned __int64)v213 & (qword_151E0C930 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v215 = (0x101010101010101LL
            * ((v214
              + (((((unsigned __int64)v213 & (qword_151E0C930 - 1))
                 - ((((unsigned __int64)v213 & (qword_151E0C930 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v214
                + (((((unsigned __int64)v213 & (qword_151E0C930 - 1))
                   - ((((unsigned __int64)v213 & (qword_151E0C930 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v216 = v211 + 23;
      if ( (qword_151E0C930 & (unsigned __int64)v213) != 0 )
      {
        v217 = *((RenderableComponent **)&v216->_Mypair._Myval2->__vftable + v215);
        v1062 = v210;
        v218 = guard_dispatch_icall_nop(a1: v217);
        v1062 = v210;
        v219 = guard_dispatch_icall_nop(a1: v217);
        if ( (v219 | v218) == 1 )
        {
          if ( v218 != 0 )
          {
            v220 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v221 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v220 != v221 )
            {
              while ( *v220 != v217 )
              {
                if ( ++v220 == v221 )
                  goto LABEL_497;
              }
            }
            if ( v220 != v221 )
            {
              v412 = v219;
              memmove_0(a1: v220, Src: v220 + 1, Size: (char *)v221 - (char *)(v220 + 1));
              v219 = v412;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_497:
          if ( v219 != 0 )
          {
            v413 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v414 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v413 != v414 )
            {
              while ( *v413 != (CustomFrameUpdateComponent *)v217 )
              {
                if ( ++v413 == v414 )
                  goto LABEL_504;
              }
            }
            if ( v413 != v414 )
            {
              memmove_0(a1: v413, Src: v413 + 1, Size: (char *)v414 - (char *)(v413 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_504:
        v415 = *((void (__fastcall ****)(_QWORD, __int64))&v216->_Mypair._Myval2->__vftable + v215);
        *((_QWORD *)&v216->_Mypair._Myval2->__vftable + v215) = v210;
        if ( v415 != nullptr )
          (**v415)(a1: v415, a2: 1);
LABEL_1181:
        v1062 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v210) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v210;
          v688 = ownerControl;
          v689 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v689 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1062 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v689);
          }
          else
          {
            *v689 = v210;
            ++v688->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1062 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v210) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v210;
          v690 = ownerControl;
          v691 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v691 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1062 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v691);
          }
          else
          {
            *v691 = (CustomFrameUpdateComponent *)v210;
            ++v690->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
LABEL_1713:
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)def);
        v43 = ownerControl;
        UIControlFactory::_populateTextToSpeechComponent(def: v1110, ownerControl, controlPriorityDefault: 1000);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v210;
      v306 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v211[23]._Mypair._Myval2 + (unsigned int)(8 * v215));
      v307 = v211[24]._Mypair._Myval2;
      if ( v307 == v211[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v211 + 23,
          _Val: v306);
        v382 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v307 == (StructureFeature *)v306 )
        {
          v307->__vftable = (StructureFeature_vtbl *)v210;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1180:
          ownerControl->mComponentsInUse |= v212;
          goto LABEL_1181;
        }
        v308 = (std::unique_ptr<RuinedPortalFeature> *)&v307[-1].mActiveBlueprintCreateCount;
        v309 = *(StructureFeature_vtbl **)&v307[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v307[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v307->__vftable = v309;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v308 != v306 )
        {
          v310 = v308[-1]._Mypair._Myval2;
          v311 = v308->_Mypair._Myval2;
          v308[-1]._Mypair._Myval2 = nullptr;
          v308->_Mypair._Myval2 = v310;
          if ( v311 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v311->dtr_StructureFeature)(a1: v311, a2: 1);
          --v308;
        }
        v382 = v306->_Mypair._Myval2;
        v306->_Mypair._Myval2 = (RuinedPortalFeature *)v210;
      }
      if ( v382 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v382->dtr_StructureFeature)(a1: v382, a2: 1);
      goto LABEL_1180;
    case 14LL:
      v58 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v58);
      UIControlFactory::_populateInputComponent(def, ownerControl: v58);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v58);
      LOBYTE(v59) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v59);
      v60 = (UIResolvedDef *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                               this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                               a2: 232);
      if ( v60 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0xE8u, alignment: 0);
      def = v60;
      ScrollViewComponent::ScrollViewComponent(owner: (UIControl *)v60);
      if ( __TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                           (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                           1u);
          `uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v61 = `uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId;
      v62 = ownerControl->mComponentsInUse;
      v63 = (((v62 & (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1))
            - (((v62 & (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1)) >> 1)
             & 0x5555555555555555LL))
           & 0x3333333333333333LL)
          + ((((v62 & (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1))
             - (((v62 & (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1)) >> 1)
              & 0x5555555555555555LL)) >> 2)
           & 0x3333333333333333LL);
      v64 = (0x101010101010101LL * ((v63 + (v63 >> 4)) & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v65 = &ownerControl->mComponents;
      v66 = def;
      if ( (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId & v62) != 0 )
      {
        v67 = (RenderableComponent *)v65->_Mypair._Myval2._Myfirst[v64]._Mypair._Myval2;
        v1060 = def;
        v68 = guard_dispatch_icall_nop(a1: v67);
        v1060 = def;
        v69 = guard_dispatch_icall_nop(a1: v67);
        if ( (v69 | v68) == 1 )
        {
          if ( v68 != 0 )
          {
            v70 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v71 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v70 != v71 )
            {
              while ( *v70 != v67 )
              {
                if ( ++v70 == v71 )
                  goto LABEL_519;
              }
            }
            if ( v70 != v71 )
            {
              v420 = v69;
              memmove_0(a1: v70, Src: v70 + 1, Size: (char *)v71 - (char *)(v70 + 1));
              v69 = v420;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_519:
          if ( v69 != 0 )
          {
            v421 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v422 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v421 != v422 )
            {
              while ( *v421 != (CustomFrameUpdateComponent *)v67 )
              {
                if ( ++v421 == v422 )
                  goto LABEL_526;
              }
            }
            if ( v421 != v422 )
            {
              memmove_0(a1: v421, Src: v421 + 1, Size: (char *)v422 - (char *)(v421 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_526:
        v423 = v65->_Mypair._Myval2._Myfirst[v64]._Mypair._Myval2;
        v66 = def;
        v65->_Mypair._Myval2._Myfirst[v64]._Mypair._Myval2 = (UIComponent *)def;
        if ( v423 != nullptr )
          ((void (__fastcall *)(UIComponent *, __int64))v423->dtr_UIComponent)(a1: v423, a2: 1);
LABEL_1220:
        v1060 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v66) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = def;
          v706 = ownerControl;
          v707 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v707 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1060 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v707);
          }
          else
          {
            *v707 = (RenderableComponent *)def;
            ++v706->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1060 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: def) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = def;
          v708 = ownerControl;
          v709 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v709 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1060 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v709);
          }
          else
          {
            *v709 = (CustomFrameUpdateComponent *)def;
            ++v708->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                             (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                             1u);
            `uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VScrollViewComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v710 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId & v710) != 0
          && (v711 = ((`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1) & v710)
                   - ((((`uicontrol_id<UIComponent,ScrollViewComponent>'::`2'::id.mBitId - 1) & v710) >> 1)
                    & 0x5555555555555555LL),
              v712 = (0x101010101010101LL
                    * (((v711 & 0x3333333333333333LL)
                      + ((v711 >> 2) & 0x3333333333333333LL)
                      + (((v711 & 0x3333333333333333LL) + ((v711 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v713 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v713 > v712) )
        {
          v714 = v713[v712]._Mypair._Myval2;
        }
        else
        {
          v714 = nullptr;
        }
        v1048._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 0;
        v1049._Mypair._Myval2._Bx._Ptr = "scrollbar_track_button";
        *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 22;
        v715 = &v1069;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &v1069,
          key: (std::string_view *)&v1049,
          defaultValue: (std::string_view *)&v1048);
        v1046._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1046._Mypair._Myval2._Bx._Alias[8] = 0;
        v1071._Mydata = "scrollbar_touch_button";
        v1071._Mysize = 22;
        p_formal = &__formal;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &__formal,
          key: &v1071,
          defaultValue: (std::string_view *)&v1046);
        memset(&v1076, 0, sizeof(v1076));
        v717 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                         this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                         a2: 32);
        if ( v717 == nullptr )
          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
        v1076._Mypair._Myval2._Bx._Ptr = v717;
        v1076._Mypair._Myval2._Mysize = 16;
        v1076._Mypair._Myval2._Myres = 31;
        *(__m128i *)v717 = _mm_loadu_si128((const __m128i *)"scrollbar.active");
        v717[16] = 0;
        memset(&v1073, 0, sizeof(v1073));
        v718 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                         this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                         a2: 32);
        if ( v718 == nullptr )
          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
        v1073._Mypair._Myval2._Bx._Ptr = v718;
        v1073._Mypair._Myval2._Mysize = 18;
        v1073._Mypair._Myval2._Myres = 31;
        *(__m128i *)v718 = _mm_loadu_si128(&xmmword_14EC8B6CA);
        strcpy(v718 + 16, "ed");
        memset(&v1072, 0, sizeof(v1072));
        v719 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                         this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                         a2: 32);
        if ( v719 == nullptr )
          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
        v1072._Mypair._Myval2._Bx._Ptr = v719;
        v1072._Mypair._Myval2._Mysize = 19;
        v1072._Mypair._Myval2._Myres = 31;
        *(__m128i *)v719 = _mm_loadu_si128(&xmmword_14EC319DE);
        strcpy(v719 + 15, "ttom");
        if ( v1076._Mypair._Myval2._Myres < 0x10 )
          v720 = &v1076;
        else
          v720 = (std::string *)v1076._Mypair._Myval2._Bx._Ptr;
        if ( v1076._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1076._Mypair._Myval2._Mysize >= 8 )
          {
            v722 = v1076._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v721 = -2128831035;
            do
            {
              v721 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v721 ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[7]);
              v720 = (std::string *)((char *)v720 + 8);
              v722 -= 8LL;
            }
            while ( v722 != 0 );
          }
          else
          {
            v721 = -2128831035;
          }
          if ( (v1076._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v723 = 0;
            do
              v721 = 16777619 * (v721 ^ (unsigned __int8)v720->_Mypair._Myval2._Bx._Buf[v723++]);
            while ( (v1076._Mypair._Myval2._Mysize & 7) != v723 );
          }
        }
        else
        {
          v721 = -2128831035;
        }
        LODWORD(v714[6].mOwner) = v721;
        if ( v1073._Mypair._Myval2._Myres < 0x10 )
          v724 = &v1073;
        else
          v724 = (std::string *)v1073._Mypair._Myval2._Bx._Ptr;
        if ( v1073._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1073._Mypair._Myval2._Mysize >= 8 )
          {
            v726 = v1073._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v725 = -2128831035;
            do
            {
              v725 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v725 ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[7]);
              v724 = (std::string *)((char *)v724 + 8);
              v726 -= 8LL;
            }
            while ( v726 != 0 );
          }
          else
          {
            v725 = -2128831035;
          }
          if ( (v1073._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v727 = 0;
            do
              v725 = 16777619 * (v725 ^ (unsigned __int8)v724->_Mypair._Myval2._Bx._Buf[v727++]);
            while ( (v1073._Mypair._Myval2._Mysize & 7) != v727 );
          }
        }
        else
        {
          v725 = -2128831035;
        }
        HIDWORD(v714[6].mOwner) = v725;
        if ( v1069._Mypair._Myval2._Myres >= 0x10 )
          v715 = (std::string *)v1069._Mypair._Myval2._Bx._Ptr;
        if ( v1069._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1069._Mypair._Myval2._Mysize >= 8 )
          {
            v729 = v1069._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v728 = -2128831035;
            do
            {
              v728 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v728 ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[7]);
              v715 = (std::string *)((char *)v715 + 8);
              v729 -= 8LL;
            }
            while ( v729 != 0 );
          }
          else
          {
            v728 = -2128831035;
          }
          if ( (v1069._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v730 = 0;
            do
              v728 = 16777619 * (v728 ^ (unsigned __int8)v715->_Mypair._Myval2._Bx._Buf[v730++]);
            while ( (v1069._Mypair._Myval2._Mysize & 7) != v730 );
          }
        }
        else
        {
          v728 = -2128831035;
        }
        LODWORD(v714[6].__vftable) = v728;
        if ( __formal._Mypair._Myval2._Myres >= 0x10 )
          p_formal = (std::string *)__formal._Mypair._Myval2._Bx._Ptr;
        if ( __formal._Mypair._Myval2._Mysize != 0 )
        {
          if ( __formal._Mypair._Myval2._Mysize >= 8 )
          {
            v732 = __formal._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v731 = -2128831035;
            do
            {
              v731 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v731 ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[7]);
              p_formal = (std::string *)((char *)p_formal + 8);
              v732 -= 8LL;
            }
            while ( v732 != 0 );
          }
          else
          {
            v731 = -2128831035;
          }
          if ( (__formal._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v733 = 0;
            do
              v731 = 16777619 * (v731 ^ (unsigned __int8)p_formal->_Mypair._Myval2._Bx._Buf[v733++]);
            while ( (__formal._Mypair._Myval2._Mysize & 7) != v733 );
          }
        }
        else
        {
          v731 = -2128831035;
        }
        HIDWORD(v714[6].__vftable) = v731;
        if ( v1072._Mypair._Myval2._Myres < 0x10 )
          v734 = &v1072;
        else
          v734 = (std::string *)v1072._Mypair._Myval2._Bx._Ptr;
        if ( v1072._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1072._Mypair._Myval2._Mysize >= 8 )
          {
            v736 = v1072._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v735 = -2128831035;
            do
            {
              v735 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v735 ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[7]);
              v734 = (std::string *)((char *)v734 + 8);
              v736 -= 8LL;
            }
            while ( v736 != 0 );
          }
          else
          {
            v735 = -2128831035;
          }
          if ( (v1072._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v737 = 0;
            do
              v735 = 16777619 * (v735 ^ (unsigned __int8)v734->_Mypair._Myval2._Bx._Buf[v737++]);
            while ( (v1072._Mypair._Myval2._Mysize & 7) != v737 );
          }
        }
        else
        {
          v735 = -2128831035;
        }
        LODWORD(v714[7].__vftable) = v735;
        *(_QWORD *)&_Args[0].mIgnored = (char *)&xmmword_14EC9272A + 9;
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v738 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v738) )
          Json::Value::isNumeric(this: v738);
        if ( Json::Value::isNumeric(this: v738) )
          *(float *)v739.m128i_i32 = Json::Value::asFloat(this: v738, defaultValue: 0.0);
        else
          v739 = _mm_cvtsi32_si128(0x3F800000u);
        HIDWORD(v714[7].mOwner) = _mm_cvtsi128_si32(v739);
        *(_QWORD *)&_Args[0].mIgnored = "gesture_control_enabled";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)23;
        v740 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v740) && !Json::Value::isBool(this: v740) )
          Json::Value::isIntegral(this: v740);
        v741 = Json::Value::isIntegral(this: v740) && Json::Value::asBool(this: v740, defaultValue: false);
        LOBYTE(v714[8].__vftable) = v741;
        *(_QWORD *)&_Args[0].mIgnored = "always_handle_scrolling";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)23;
        v742 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v742) && !Json::Value::isBool(this: v742) )
          Json::Value::isIntegral(this: v742);
        v743 = Json::Value::isIntegral(this: v742) && Json::Value::asBool(this: v742, defaultValue: false);
        BYTE1(v714[8].__vftable) = v743;
        *(_QWORD *)&_Args[0].mIgnored = "touch_mode";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)10;
        v744 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v744) && !Json::Value::isBool(this: v744) )
          Json::Value::isIntegral(this: v744);
        v745 = Json::Value::isIntegral(this: v744) && Json::Value::asBool(this: v744, defaultValue: false);
        BYTE2(v714[8].__vftable) = v745;
        *(_QWORD *)&_Args[0].mIgnored = "allow_scroll_even_when_content_fits";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)35;
        v746 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v746) && !Json::Value::isBool(this: v746) )
          Json::Value::isIntegral(this: v746);
        v747 = Json::Value::isIntegral(this: v746);
        v748 = true;
        if ( v747 )
          v748 = Json::Value::asBool(this: v746, defaultValue: false);
        BYTE3(v714[8].__vftable) = v748;
        *(_QWORD *)&_Args[0].mIgnored = "scrollbar_always_visible";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)24;
        v749 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v749) && !Json::Value::isBool(this: v749) )
          Json::Value::isIntegral(this: v749);
        v750 = Json::Value::isIntegral(this: v749) && Json::Value::asBool(this: v749, defaultValue: false);
        BYTE4(v714[8].__vftable) = v750;
        *(_QWORD *)&_Args[0].mIgnored = off_14E8D6F70;
        _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
        v1041._Mydata = u;
        v1041._Mysize = 0;
        v1042._Mydata = "scrollbar_box";
        v1042._Mysize = 13;
        v1100 = 1;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)&v1079, key: &v1042, defaultValue: &v1041);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1079,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v751 = *(void **)&v1079.mIgnored;
          v752 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v752 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v751 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v751, __formal: v752);
        }
        *(_QWORD *)&v1079.mIgnored = off_14E8D6FA0;
        v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
        v1043._Mydata = u;
        v1043._Mysize = 0;
        v1044._Mydata = "scrollbar_track";
        v1044._Mysize = 15;
        v1099 = 1;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)&defaultValue, key: &v1044, defaultValue: &v1043);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&defaultValue,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
        {
          v753 = *(void **)&defaultValue.mFileSystem;
          v754 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
          if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v754 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
            v753 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
          }
          operator delete(block: v753, __formal: v754);
        }
        *(_QWORD *)&defaultValue.mFileSystem = off_14E8D6FD0;
        v1078 = &defaultValue;
        v1045._Mydata = u;
        v1045._Mysize = 0;
        v1033._Mydata = "scroll_view_port";
        v1033._Mysize = 16;
        v1098 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &Src, key: &v1033, defaultValue: &v1045);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&Src,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( Src._Mypair._Myval2._Myres >= 0x10 )
        {
          v755 = Src._Mypair._Myval2._Bx._Ptr;
          v756 = Src._Mypair._Myval2._Myres + 1;
          if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v756 = Src._Mypair._Myval2._Myres + 40;
            v755 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v755, __formal: v756);
        }
        Src._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7000;
        p_Src = &Src;
        v1034._Mydata = u;
        v1034._Mysize = 0;
        v1035._Mydata = "scroll_content";
        v1035._Mysize = 14;
        v1097 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &v1106, key: &v1035, defaultValue: &v1034);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1106,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1106._Mypair._Myval2._Myres >= 0x10 )
        {
          v757 = v1106._Mypair._Myval2._Bx._Ptr;
          v758 = v1106._Mypair._Myval2._Myres + 1;
          if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v758 = v1106._Mypair._Myval2._Myres + 40;
            v757 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v757, __formal: v758);
        }
        v1106._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7030;
        v1107 = &v1106;
        v1036._Mydata = u;
        v1036._Mysize = 0;
        v1037._Mydata = "scroll_box_and_track_panel";
        v1037._Mysize = 26;
        v1096 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &v1068, key: &v1037, defaultValue: &v1036);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1068,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1068._Mypair._Myval2._Myres >= 0x10 )
        {
          v759 = v1068._Mypair._Myval2._Bx._Ptr;
          v760 = v1068._Mypair._Myval2._Myres + 1;
          if ( v1068._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1068._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1068._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v760 = v1068._Mypair._Myval2._Myres + 40;
            v759 = *((char **)v1068._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v759, __formal: v760);
        }
        v1068._Mypair._Myval2._Bx._Ptr = "jump_to_bottom_on_update";
        *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 24;
        v761 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1068, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v761) && !Json::Value::isBool(this: v761) )
          Json::Value::isIntegral(this: v761);
        v762 = Json::Value::isIntegral(this: v761) && Json::Value::asBool(this: v761, defaultValue: false);
        BYTE4(v714[13].mOwner) = v762;
        if ( v1072._Mypair._Myval2._Myres >= 0x10 )
        {
          v763 = v1072._Mypair._Myval2._Bx._Ptr;
          v764 = v1072._Mypair._Myval2._Myres + 1;
          if ( v1072._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1072._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1072._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v764 = v1072._Mypair._Myval2._Myres + 40;
            v763 = *((char **)v1072._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v763, __formal: v764);
        }
        if ( v1073._Mypair._Myval2._Myres >= 0x10 )
        {
          v765 = v1073._Mypair._Myval2._Bx._Ptr;
          v766 = v1073._Mypair._Myval2._Myres + 1;
          if ( v1073._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1073._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1073._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v766 = v1073._Mypair._Myval2._Myres + 40;
            v765 = *((char **)v1073._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v765, __formal: v766);
        }
        if ( v1076._Mypair._Myval2._Myres >= 0x10 )
        {
          v767 = v1076._Mypair._Myval2._Bx._Ptr;
          v768 = v1076._Mypair._Myval2._Myres + 1;
          if ( v1076._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1076._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1076._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v768 = v1076._Mypair._Myval2._Myres + 40;
            v767 = *((char **)v1076._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v767, __formal: v768);
        }
        if ( __formal._Mypair._Myval2._Myres >= 0x10 )
        {
          v769 = __formal._Mypair._Myval2._Bx._Ptr;
          v770 = __formal._Mypair._Myval2._Myres + 1;
          if ( __formal._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&__formal._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)__formal._Mypair._Myval2._Bx._Ptr - 1)
                                                                    - 8] >= 0x20 )
              goto LABEL_1922;
            v770 = __formal._Mypair._Myval2._Myres + 40;
            v769 = *((char **)__formal._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v769, __formal: v770);
        }
        if ( v1069._Mypair._Myval2._Myres >= 0x10 )
        {
          v771 = v1069._Mypair._Myval2._Bx._Ptr;
          v772 = v1069._Mypair._Myval2._Myres + 1;
          if ( v1069._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1069._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1069._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v772 = v1069._Mypair._Myval2._Myres + 40;
            v771 = *((char **)v1069._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v771, __formal: v772);
        }
LABEL_1387:
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1108);
LABEL_1733:
        v43 = ownerControl;
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = def;
      v318 = (std::unique_ptr<RuinedPortalFeature> *)((char *)ownerControl->mComponents._Mypair._Myval2._Myfirst
                                                    + (unsigned int)(8 * v64));
      v319 = ownerControl->mComponents._Mypair._Myval2._Mylast;
      if ( v319 == ownerControl->mComponents._Mypair._Myval2._Myend )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: (std::unique_ptr<StructureFeature> *)&ownerControl->mComponents,
          _Val: v318);
        v384 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v319 == (std::unique_ptr<UIComponent> *)v318 )
        {
          v319->_Mypair._Myval2 = (UIComponent *)def;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1219:
          ownerControl->mComponentsInUse |= v61;
          goto LABEL_1220;
        }
        v320 = (std::unique_ptr<RuinedPortalFeature> *)&v319[-1];
        v321 = v319[-1]._Mypair._Myval2;
        v319[-1]._Mypair._Myval2 = nullptr;
        v319->_Mypair._Myval2 = v321;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v320 != v318 )
        {
          v322 = v320[-1]._Mypair._Myval2;
          v323 = v320->_Mypair._Myval2;
          v320[-1]._Mypair._Myval2 = nullptr;
          v320->_Mypair._Myval2 = v322;
          if ( v323 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v323->dtr_StructureFeature)(a1: v323, a2: 1);
          --v320;
        }
        v384 = v318->_Mypair._Myval2;
        v318->_Mypair._Myval2 = (RuinedPortalFeature *)v66;
      }
      if ( v384 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v384->dtr_StructureFeature)(a1: v384, a2: 1);
      goto LABEL_1219;
    case 15LL:
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      LOBYTE(v119) = 27;
      LOBYTE(v1080) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v119);
      v120 = (UIControl *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                            this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                            a2: 152);
      if ( v120 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x98u, alignment: 0);
      v1108 = (RuinedPortalFeature *)v120;
      SelectionWheelComponent::SelectionWheelComponent(owner: v120);
      if ( __TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                               (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                               1u);
          `uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v121 = `uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId;
      v122 = ownerControl->mComponentsInUse;
      v123 = (((v122 & (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1))
             - (((v122 & (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1)) >> 1)
              & 0x5555555555555555LL))
            & 0x3333333333333333LL)
           + ((((v122 & (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1))
              - (((v122 & (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1)) >> 1)
               & 0x5555555555555555LL)) >> 2)
            & 0x3333333333333333LL);
      v124 = (0x101010101010101LL * ((v123 + (v123 >> 4)) & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v125 = &ownerControl->mComponents;
      v126 = v1108;
      if ( (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId & v122) != 0 )
      {
        v127 = (RenderableComponent *)v125->_Mypair._Myval2._Myfirst[v124]._Mypair._Myval2;
        v1056 = v1108;
        v128 = guard_dispatch_icall_nop(a1: v127);
        v1056 = v1108;
        v129 = guard_dispatch_icall_nop(a1: v127);
        if ( (v129 | v128) == 1 )
        {
          if ( v128 != 0 )
          {
            v130 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v131 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v130 != v131 )
            {
              while ( *v130 != v127 )
              {
                if ( ++v130 == v131 )
                  goto LABEL_442;
              }
            }
            if ( v130 != v131 )
            {
              v392 = v129;
              memmove_0(a1: v130, Src: v130 + 1, Size: (char *)v131 - (char *)(v130 + 1));
              v129 = v392;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_442:
          if ( v129 != 0 )
          {
            v393 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v394 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v393 != v394 )
            {
              while ( *v393 != (CustomFrameUpdateComponent *)v127 )
              {
                if ( ++v393 == v394 )
                  goto LABEL_449;
              }
            }
            if ( v393 != v394 )
            {
              memmove_0(a1: v393, Src: v393 + 1, Size: (char *)v394 - (char *)(v393 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_449:
        v395 = v125->_Mypair._Myval2._Myfirst[v124]._Mypair._Myval2;
        v126 = v1108;
        v125->_Mypair._Myval2._Myfirst[v124]._Mypair._Myval2 = (UIComponent *)v1108;
        if ( v395 != nullptr )
          ((void (__fastcall *)(UIComponent *, __int64))v395->dtr_UIComponent)(a1: v395, a2: 1);
LABEL_607:
        v1056 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v126) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v1108;
          v452 = ownerControl;
          v453 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v453 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1056 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v453);
          }
          else
          {
            *v453 = (RenderableComponent *)v1108;
            ++v452->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1056 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v1108) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v1108;
          v454 = ownerControl;
          v455 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v455 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1056 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v455);
          }
          else
          {
            *v455 = (CustomFrameUpdateComponent *)v1108;
            ++v454->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                                 (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                                 1u);
            `uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSelectionWheelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v456 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId & v456) != 0
          && (v457 = ((`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1) & v456)
                   - ((((`uicontrol_id<UIComponent,SelectionWheelComponent>'::`2'::id.mBitId - 1) & v456) >> 1)
                    & 0x5555555555555555LL),
              v458 = (0x101010101010101LL
                    * (((v457 & 0x3333333333333333LL)
                      + ((v457 >> 2) & 0x3333333333333333LL)
                      + (((v457 & 0x3333333333333333LL) + ((v457 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v459 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v459 > v458) )
        {
          v1108 = (RuinedPortalFeature *)v459[v458]._Mypair._Myval2;
        }
        else
        {
          v1108 = nullptr;
        }
        *(_QWORD *)&_Args[0].mIgnored = "consume_event";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)13;
        v460 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v460) && !Json::Value::isBool(this: v460) )
          Json::Value::isIntegral(this: v460);
        v461 = Json::Value::isIntegral(this: v460);
        v462 = true;
        if ( v461 )
          v462 = Json::Value::asBool(this: v460, defaultValue: false);
        LOBYTE(v1108->mCachedStructures._Traitsobj._Mypair._Myval2._Myval2) = v462;
        *(_QWORD *)&_Args[0].mIgnored = "slice_count";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)11;
        v463 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v463) )
          Json::Value::isNumeric(this: v463);
        v464 = Json::Value::isInt(this: v463);
        v465 = 1;
        if ( v464 )
          v465 = Json::Value::asInt(this: v463, defaultValue: 0);
        v1108->mCachedStructures._List._Mypair._Myval2._Myhead = (std::_List_node<std::pair<const ChunkPos,std::unique_ptr<StructureStart> >,void *> *)v465;
        *(_QWORD *)&_Args[0].mIgnored = "inner_radius";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v466 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v466) )
          Json::Value::isNumeric(this: v466);
        isNumeric = Json::Value::isNumeric(this: v466);
        v468 = 0;
        if ( isNumeric )
          *(float *)v468.m128i_i32 = Json::Value::asFloat(this: v466, defaultValue: 0.0);
        LODWORD(v1108->mCachedStructures._Vec._Mypair._Myval2._Mylast) = _mm_cvtsi128_si32(v468);
        *(_QWORD *)&_Args[0].mIgnored = "outer_radius";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v469 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v469) )
          Json::Value::isNumeric(this: v469);
        if ( Json::Value::isNumeric(this: v469) )
          *(float *)v470.m128i_i32 = Json::Value::asFloat(this: v469, defaultValue: 0.0);
        else
          v470 = _mm_cvtsi32_si128(0x3F800000u);
        HIDWORD(v1108->mCachedStructures._Vec._Mypair._Myval2._Mylast) = _mm_cvtsi128_si32(v470);
        v1106._Mypair._Myval2._Bx._Ptr = "state_controls";
        *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = 14;
        v471 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&v1106, a3: false);
        if ( !Json::Value::isArray(this: v471) )
          ContentLogHelper::_contentLog<char const (&)[185]>(
            level: true,
            area: (const LogLevel)3,
            args: UI,
            a4: (const char (*)[150])"JSON UI parse failure: Must define state_controls as an array!");
        if ( Json::Value::isArray(this: v471) )
        {
          Json::Value::begin(this: v471, result: (Json::ValueConstIterator *)&v1069);
          Json::Value::end(this: v471, result: (Json::ValueConstIterator *)&__formal);
          p_Mysize = &def->mUnvalidatedProperties._Mypair._Myval2._Myval2._Mysize;
          if ( !Json::ValueIteratorBase::isEqual(
                  this: (Json::ValueIteratorBase *)&v1069,
                  other: (const Json::ValueIteratorBase *)&__formal) )
          {
            v475 = Json::ValueIteratorBase::deref(this: (Json::ValueIteratorBase *)&v1069);
            if ( Json::Value::isObject(this: v475) )
            {
              *(_OWORD *)&defaultValue.mFileSystem = (unsigned __int64)u;
              Src._Mypair._Myval2._Bx._Ptr = (char *)u;
              *(_QWORD *)&Src._Mypair._Myval2._Bx._Alias[8] = 0;
              UIResolvedDef::UIResolvedDef(
                this: _Args,
                variablesStack: (std::vector<Json::Value *> *)p_Mysize,
                defNamespace: (std::string_view *)&Src,
                defName: (std::string_view *)&defaultValue,
                a5: v475,
                a6: v475);
              if ( !_Args[0].mIgnored )
              {
                v1076._Mypair._Myval2._Bx._Ptr = (char *)u;
                *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 0;
                v1073._Mypair._Myval2._Bx._Ptr = "control_name";
                *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 12;
                UIResolvedDef::getAsString(
                  this: _Args,
                  result: (std::string *)&defaultValue,
                  key: (std::string_view *)&v1073,
                  defaultValue: (std::string_view *)&v1076);
                *(_QWORD *)&v1079.mIgnored = off_14E8D7510;
                v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
                UIControl::_registerControlNameResolver(
                  controlName: (const std::string *)ownerControl,
                  scope: (ui::NameResolutionScope)&defaultValue,
                  setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
                if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
                {
                  v476 = *(void **)&defaultValue.mFileSystem;
                  v477 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
                  if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
                  {
                    if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                          - 8LL
                                          - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
                      goto LABEL_1922;
                    v477 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
                    v476 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
                  }
                  operator delete(block: v476, __formal: v477);
                }
              }
              UIResolvedDef::~UIResolvedDef(this: _Args);
            }
            JUMPOUT(0x14458C157LL);
          }
          webrtc::VideoSinkInterface<webrtc::VideoFrame>::OnConstraintsChanged(&__formal, __formal: v474);
          webrtc::VideoSinkInterface<webrtc::VideoFrame>::OnConstraintsChanged(__formal: &v1069, __formal: v478);
        }
        *(_QWORD *)&defaultValue.mFileSystem = u;
        defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = nullptr;
        Src._Mypair._Myval2._Bx._Ptr = "analog_button_name";
        *(_QWORD *)&Src._Mypair._Myval2._Bx._Alias[8] = 18;
        v479 = (unsigned __int8 *)_Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: (std::string_view *)&Src,
          (std::string_view *)&defaultValue);
        v480 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        v481 = *(_QWORD **)&_Args[0].mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v479 = *(unsigned __int8 **)&_Args[0].mIgnored;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v483 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v482 = -2128831035;
            do
            {
              v482 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v482 ^ *v479)) ^ v479[1])) ^ v479[2])) ^ v479[3]))
                          ^ v479[4]))
                        ^ v479[5]))
                      ^ v479[6]))
                    ^ v479[7]);
              v479 += 8;
              v483 -= 8LL;
            }
            while ( v483 != 0 );
          }
          else
          {
            v482 = -2128831035;
          }
          if ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v484 = 0;
            do
              v482 = 16777619 * (v482 ^ v479[v484++]);
            while ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != v484 );
          }
        }
        else
        {
          v482 = -2128831035;
        }
        LODWORD(v1108->mCachedStructures._Vec._Mypair._Myval2._Myend) = v482;
        if ( v480 >= 0x10 )
        {
          v485 = v480 + 1;
          if ( v480 + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)v481 - *(v481 - 1) - 8 >= 0x20 )
              goto LABEL_1922;
            v485 = v480 + 40;
            v481 = (_QWORD *)*(v481 - 1);
          }
          operator delete(block: v481, __formal: v485);
        }
        v1069._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 0;
        __formal._Mypair._Myval2._Bx._Ptr = "hover_button_name";
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 17;
        v486 = (unsigned __int8 *)_Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: (std::string_view *)&__formal,
          defaultValue: (std::string_view *)&v1069);
        v487 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        v488 = *(_QWORD **)&_Args[0].mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v486 = *(unsigned __int8 **)&_Args[0].mIgnored;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v490 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v489 = -2128831035;
            do
            {
              v489 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v489 ^ *v486)) ^ v486[1])) ^ v486[2])) ^ v486[3]))
                          ^ v486[4]))
                        ^ v486[5]))
                      ^ v486[6]))
                    ^ v486[7]);
              v486 += 8;
              v490 -= 8LL;
            }
            while ( v490 != 0 );
          }
          else
          {
            v489 = -2128831035;
          }
          if ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v491 = 0;
            do
              v489 = 16777619 * (v489 ^ v486[v491++]);
            while ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != v491 );
          }
        }
        else
        {
          v489 = -2128831035;
        }
        LODWORD(v1108->mCachedStructures._Mask) = v489;
        if ( v487 >= 0x10 )
        {
          v492 = v487 + 1;
          if ( v487 + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)v488 - *(v488 - 1) - 8 >= 0x20 )
              goto LABEL_1922;
            v492 = v487 + 40;
            v488 = (_QWORD *)*(v488 - 1);
          }
          operator delete(block: v488, __formal: v492);
        }
        v1072._Mypair._Myval2._Bx = (std::_String_val<std::_Simple_types<char> >::_Bxty)(unsigned __int64)u;
        v1068._Mypair._Myval2._Bx._Ptr = "select_button_name";
        *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 18;
        v493 = (unsigned __int8 *)_Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: (std::string_view *)&v1068,
          defaultValue: (std::string_view *)&v1072);
        v494 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        v495 = *(_QWORD **)&_Args[0].mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v493 = *(unsigned __int8 **)&_Args[0].mIgnored;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v497 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v496 = -2128831035;
            do
            {
              v496 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v496 ^ *v493)) ^ v493[1])) ^ v493[2])) ^ v493[3]))
                          ^ v493[4]))
                        ^ v493[5]))
                      ^ v493[6]))
                    ^ v493[7]);
              v493 += 8;
              v497 -= 8LL;
            }
            while ( v497 != 0 );
          }
          else
          {
            v496 = -2128831035;
          }
          if ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v498 = 0;
            do
              v496 = 16777619 * (v496 ^ v493[v498++]);
            while ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != v498 );
          }
        }
        else
        {
          v496 = -2128831035;
        }
        HIDWORD(v1108->mCachedStructures._Vec._Mypair._Myval2._Myend) = v496;
        if ( v494 >= 0x10 )
        {
          v499 = v494 + 1;
          if ( v494 + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)v495 - *(v495 - 1) - 8 >= 0x20 )
              goto LABEL_1922;
            v499 = v494 + 40;
            v495 = (_QWORD *)*(v495 - 1);
          }
          operator delete(block: v495, __formal: v499);
        }
        v1048._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 0;
        v1049._Mypair._Myval2._Bx._Ptr = "iterate_left_button_name";
        *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 24;
        v500 = (unsigned __int8 *)_Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: (std::string_view *)&v1049,
          defaultValue: (std::string_view *)&v1048);
        v501 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        v502 = *(_QWORD **)&_Args[0].mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v500 = *(unsigned __int8 **)&_Args[0].mIgnored;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v504 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v503 = -2128831035;
            do
            {
              v503 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v503 ^ *v500)) ^ v500[1])) ^ v500[2])) ^ v500[3]))
                          ^ v500[4]))
                        ^ v500[5]))
                      ^ v500[6]))
                    ^ v500[7]);
              v500 += 8;
              v504 -= 8LL;
            }
            while ( v504 != 0 );
          }
          else
          {
            v503 = -2128831035;
          }
          if ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v505 = 0;
            do
              v503 = 16777619 * (v503 ^ v500[v505++]);
            while ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != v505 );
          }
        }
        else
        {
          v503 = -2128831035;
        }
        HIDWORD(v1108->mCachedStructures._Mask) = v503;
        if ( v501 >= 0x10 )
        {
          v506 = v501 + 1;
          if ( v501 + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)v502 - *(v502 - 1) - 8 >= 0x20 )
              goto LABEL_1922;
            v506 = v501 + 40;
            v502 = (_QWORD *)*(v502 - 1);
          }
          operator delete(block: v502, __formal: v506);
        }
        v1046._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1046._Mypair._Myval2._Bx._Alias[8] = 0;
        v1071._Mydata = "iterate_right_button_name";
        v1071._Mysize = 25;
        v507 = (unsigned __int8 *)_Args;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)_Args,
          key: &v1071,
          defaultValue: (std::string_view *)&v1046);
        v508 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize;
        v509 = *(_QWORD **)&_Args[0].mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v507 = *(unsigned __int8 **)&_Args[0].mIgnored;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
        {
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] >= 8u )
          {
            v511 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] & 0xFFFFFFFFFFFFFFF8uLL;
            v510 = -2128831035;
            do
            {
              v510 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619 * ((16777619 * ((16777619 * (v510 ^ *v507)) ^ v507[1])) ^ v507[2])) ^ v507[3]))
                          ^ v507[4]))
                        ^ v507[5]))
                      ^ v507[6]))
                    ^ v507[7]);
              v507 += 8;
              v511 -= 8LL;
            }
            while ( v511 != 0 );
          }
          else
          {
            v510 = -2128831035;
          }
          if ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != 0 )
          {
            v512 = 0;
            do
              v510 = 16777619 * (v510 ^ v507[v512++]);
            while ( (_Args[0].mDefNamespace._Mypair._Myval2._Bx._Buf[8] & 7) != v512 );
          }
        }
        else
        {
          v510 = -2128831035;
        }
        LODWORD(v1108->mCachedStructures._Maxidx) = v510;
        if ( v508 >= 0x10 )
        {
          v513 = v508 + 1;
          if ( v508 + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)v509 - *(v509 - 1) - 8 >= 0x20 )
              goto LABEL_1922;
            v513 = v508 + 40;
            v509 = (_QWORD *)*(v509 - 1);
          }
          operator delete(block: v509, __formal: v513);
        }
        *(_QWORD *)&_Args[0].mIgnored = "initial_button_slice";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)20;
        v514 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v514) )
          Json::Value::isNumeric(this: v514);
        isUInt = Json::Value::isUInt(this: v514);
        v516 = -1;
        if ( isUInt )
          v516 = Json::Value::asUInt(this: v514, defaultValue: 0);
        v517 = -1;
        if ( v1108->mCachedStructures._List._Mypair._Myval2._Myhead > (std::_List_node<std::pair<const ChunkPos,std::unique_ptr<StructureStart> >,void *> *)v516 )
          v517 = v516;
        v1108->mCachedStructures._List._Mypair._Myval2._Mysize = v517;
        SelectionWheelComponent::_updateControlVisibility();
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1080);
        v518 = (UIControl *)v1110;
        v43 = ownerControl;
        UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v1110);
        UIControlFactory::_populateFocusComponent(def, ownerControl: v518);
        UIControlFactory::_populateInputComponent(def, ownerControl: v518);
        UIControlFactory::_populateLayoutComponent(def, ownerControl: v518);
        UIControlFactory::_populateSoundComponent(def, ownerControl: v518, a3: (bool)v43);
        UIControlFactory::_populateTextToSpeechComponent(
          def: (const UIResolvedDef *)v518,
          ownerControl: v43,
          controlPriorityDefault: 1000);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v1108;
      v276 = (std::unique_ptr<RuinedPortalFeature> *)((char *)ownerControl->mComponents._Mypair._Myval2._Myfirst
                                                    + (unsigned int)(8 * v124));
      v277 = ownerControl->mComponents._Mypair._Myval2._Mylast;
      if ( v277 == ownerControl->mComponents._Mypair._Myval2._Myend )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: (std::unique_ptr<StructureFeature> *)&ownerControl->mComponents,
          _Val: v276);
        v377 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v277 == (std::unique_ptr<UIComponent> *)v276 )
        {
          v277->_Mypair._Myval2 = (UIComponent *)v1108;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_606:
          ownerControl->mComponentsInUse |= v121;
          goto LABEL_607;
        }
        v278 = (std::unique_ptr<RuinedPortalFeature> *)&v277[-1];
        v279 = v277[-1]._Mypair._Myval2;
        v277[-1]._Mypair._Myval2 = nullptr;
        v277->_Mypair._Myval2 = v279;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v278 != v276 )
        {
          v280 = v278[-1]._Mypair._Myval2;
          v281 = v278->_Mypair._Myval2;
          v278[-1]._Mypair._Myval2 = nullptr;
          v278->_Mypair._Myval2 = v280;
          if ( v281 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v281->dtr_StructureFeature)(a1: v281, a2: 1);
          --v278;
        }
        v377 = v276->_Mypair._Myval2;
        v276->_Mypair._Myval2 = v126;
      }
      if ( v377 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v377->dtr_StructureFeature)(a1: v377, a2: 1);
      goto LABEL_606;
    case 16LL:
      v44 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v44);
      UIControlFactory::_populateInputComponent(def, ownerControl: v44);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v44);
      LOBYTE(v45) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v45);
      v46 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                      a2: 264);
      if ( v46 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x108u, alignment: 0);
      v47 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v46 + 1) = ownerControl;
      *(_QWORD *)v46 = &off_14E8D6130;
      *((_OWORD *)v46 + 1) = 0;
      *((_OWORD *)v46 + 2) = 0;
      *(_QWORD *)(v46 + 46) = 0;
      v46[54] = 2;
      *(_QWORD *)(v46 + 55) = 0;
      v46[63] = 0;
      *((_QWORD *)v46 + 8) = 1;
      v46[76] = 0;
      *((_QWORD *)v46 + 10) = 0;
      v46[88] = 0;
      *((_DWORD *)v46 + 23) = -1;
      *((_OWORD *)v46 + 6) = 0;
      *((_QWORD *)v46 + 14) = 0;
      *((_QWORD *)v46 + 15) = 15;
      v46[128] = 0;
      *(_OWORD *)(v46 + 232) = 0;
      *(_OWORD *)(v46 + 216) = 0;
      *(_OWORD *)(v46 + 200) = 0;
      *(_OWORD *)(v46 + 184) = 0;
      *(_OWORD *)(v46 + 168) = 0;
      *(_OWORD *)(v46 + 152) = 0;
      *(_OWORD *)(v46 + 136) = 0;
      *((_QWORD *)v46 + 31) = 0;
      *((_QWORD *)v46 + 32) = 15;
      if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                       (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                       1u);
          `uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v48 = `uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId;
      v49 = v47[22]._Mypair._Myval2;
      v50 = (((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1))
           - ((((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1)) >> 1)
            & 0x5555555555555555LL))
          & 0x3333333333333333LL;
      v51 = (0x101010101010101LL
           * ((v50
             + (((((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1))
                - ((((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1)) >> 1)
                 & 0x5555555555555555LL)) >> 2)
              & 0x3333333333333333LL)
             + ((v50
               + (((((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1))
                  - ((((unsigned __int64)v49 & (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1)) >> 1)
                   & 0x5555555555555555LL)) >> 2)
                & 0x3333333333333333LL)) >> 4))
            & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v52 = v47 + 23;
      if ( (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId & (unsigned __int64)v49) != 0 )
      {
        v53 = *((RenderableComponent **)&v52->_Mypair._Myval2->__vftable + v51);
        v1059 = v46;
        v54 = guard_dispatch_icall_nop(a1: v53);
        v1059 = v46;
        v55 = guard_dispatch_icall_nop(a1: v53);
        if ( (v55 | v54) == 1 )
        {
          if ( v54 != 0 )
          {
            v56 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v57 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v56 != v57 )
            {
              while ( *v56 != v53 )
              {
                if ( ++v56 == v57 )
                  goto LABEL_475;
              }
            }
            if ( v56 != v57 )
            {
              v404 = v55;
              memmove_0(a1: v56, Src: v56 + 1, Size: (char *)v57 - (char *)(v56 + 1));
              v55 = v404;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_475:
          if ( v55 != 0 )
          {
            v405 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v406 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v405 != v406 )
            {
              while ( *v405 != (CustomFrameUpdateComponent *)v53 )
              {
                if ( ++v405 == v406 )
                  goto LABEL_482;
              }
            }
            if ( v405 != v406 )
            {
              memmove_0(a1: v405, Src: v405 + 1, Size: (char *)v406 - (char *)(v405 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_482:
        v407 = *((void (__fastcall ****)(_QWORD, __int64))&v52->_Mypair._Myval2->__vftable + v51);
        *((_QWORD *)&v52->_Mypair._Myval2->__vftable + v51) = v46;
        if ( v407 != nullptr )
          (**v407)(a1: v407, a2: 1);
LABEL_841:
        v1059 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v46) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v46;
          v552 = ownerControl;
          v553 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v553 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1059 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v553);
          }
          else
          {
            *v553 = (RenderableComponent *)v46;
            ++v552->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1059 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v46) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v46;
          v554 = ownerControl;
          v555 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v555 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1059 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v555);
          }
          else
          {
            *v555 = (CustomFrameUpdateComponent *)v46;
            ++v554->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                         (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                         1u);
            `uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v556 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId & v556) != 0
          && (v557 = ((`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1) & v556)
                   - ((((`uicontrol_id<UIComponent,SliderComponent>'::`2'::id.mBitId - 1) & v556) >> 1)
                    & 0x5555555555555555LL),
              v558 = (0x101010101010101LL
                    * (((v557 & 0x3333333333333333LL)
                      + ((v557 >> 2) & 0x3333333333333333LL)
                      + (((v557 & 0x3333333333333333LL) + ((v557 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v559 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v559 > v558) )
        {
          v560 = v559[v558]._Mypair._Myval2;
        }
        else
        {
          v560 = nullptr;
        }
        v1071._Mydata = u;
        v1071._Mysize = 0;
        v1041._Mydata = "slider_track_button";
        v1041._Mysize = 19;
        v561 = &v1076;
        UIResolvedDef::getAsString(this: v1110, result: &v1076, key: &v1041, defaultValue: &v1071);
        if ( v1076._Mypair._Myval2._Myres >= 0x10 )
          v561 = (std::string *)v1076._Mypair._Myval2._Bx._Ptr;
        if ( v1076._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1076._Mypair._Myval2._Mysize >= 8 )
          {
            v563 = v1076._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v562 = -2128831035;
            do
            {
              v562 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v562 ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[7]);
              v561 = (std::string *)((char *)v561 + 8);
              v563 -= 8LL;
            }
            while ( v563 != 0 );
          }
          else
          {
            v562 = -2128831035;
          }
          if ( (v1076._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v564 = 0;
            do
              v562 = 16777619 * (v562 ^ (unsigned __int8)v561->_Mypair._Myval2._Bx._Buf[v564++]);
            while ( (v1076._Mypair._Myval2._Mysize & 7) != v564 );
          }
        }
        else
        {
          v562 = -2128831035;
        }
        LODWORD(v560[2].__vftable) = v562;
        v1042._Mydata = u;
        v1042._Mysize = 0;
        v1043._Mydata = "slider_small_decrease_button";
        v1043._Mysize = 28;
        v565 = &v1073;
        UIResolvedDef::getAsString(this: v1110, result: &v1073, key: &v1043, defaultValue: &v1042);
        if ( v1073._Mypair._Myval2._Myres >= 0x10 )
          v565 = (std::string *)v1073._Mypair._Myval2._Bx._Ptr;
        if ( v1073._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1073._Mypair._Myval2._Mysize >= 8 )
          {
            v567 = v1073._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v566 = -2128831035;
            do
            {
              v566 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v566 ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[7]);
              v565 = (std::string *)((char *)v565 + 8);
              v567 -= 8LL;
            }
            while ( v567 != 0 );
          }
          else
          {
            v566 = -2128831035;
          }
          if ( (v1073._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v568 = 0;
            do
              v566 = 16777619 * (v566 ^ (unsigned __int8)v565->_Mypair._Myval2._Bx._Buf[v568++]);
            while ( (v1073._Mypair._Myval2._Mysize & 7) != v568 );
          }
        }
        else
        {
          v566 = -2128831035;
        }
        HIDWORD(v560[2].__vftable) = v566;
        v1044._Mydata = u;
        v1044._Mysize = 0;
        v1045._Mydata = "slider_small_increase_button";
        v1045._Mysize = 28;
        v569 = &v1072;
        UIResolvedDef::getAsString(this: v1110, result: &v1072, key: &v1045, defaultValue: &v1044);
        if ( v1072._Mypair._Myval2._Myres >= 0x10 )
          v569 = (std::string *)v1072._Mypair._Myval2._Bx._Ptr;
        if ( v1072._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1072._Mypair._Myval2._Mysize >= 8 )
          {
            v571 = v1072._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v570 = -2128831035;
            do
            {
              v570 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v570 ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[7]);
              v569 = (std::string *)((char *)v569 + 8);
              v571 -= 8LL;
            }
            while ( v571 != 0 );
          }
          else
          {
            v570 = -2128831035;
          }
          if ( (v1072._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v572 = 0;
            do
              v570 = 16777619 * (v570 ^ (unsigned __int8)v569->_Mypair._Myval2._Bx._Buf[v572++]);
            while ( (v1072._Mypair._Myval2._Mysize & 7) != v572 );
          }
        }
        else
        {
          v570 = -2128831035;
        }
        LODWORD(v560[2].mOwner) = v570;
        v1033._Mydata = u;
        v1033._Mysize = 0;
        v1034._Mydata = "slider_selected_button";
        v1034._Mysize = 22;
        v573 = &v1068;
        UIResolvedDef::getAsString(this: v1110, result: &v1068, key: &v1034, defaultValue: &v1033);
        if ( v1068._Mypair._Myval2._Myres >= 0x10 )
          v573 = (std::string *)v1068._Mypair._Myval2._Bx._Ptr;
        if ( v1068._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1068._Mypair._Myval2._Mysize >= 8 )
          {
            v575 = v1068._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v574 = -2128831035;
            do
            {
              v574 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v574 ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[7]);
              v573 = (std::string *)((char *)v573 + 8);
              v575 -= 8LL;
            }
            while ( v575 != 0 );
          }
          else
          {
            v574 = -2128831035;
          }
          if ( (v1068._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v576 = 0;
            do
              v574 = 16777619 * (v574 ^ (unsigned __int8)v573->_Mypair._Myval2._Bx._Buf[v576++]);
            while ( (v1068._Mypair._Myval2._Mysize & 7) != v576 );
          }
        }
        else
        {
          v574 = -2128831035;
        }
        HIDWORD(v560[2].mOwner) = v574;
        v1035._Mydata = u;
        v1035._Mysize = 0;
        v1036._Mydata = "slider_deselected_button";
        v1036._Mysize = 24;
        v577 = &v1048;
        UIResolvedDef::getAsString(this: v1110, result: &v1048, key: &v1036, defaultValue: &v1035);
        if ( v1048._Mypair._Myval2._Myres >= 0x10 )
          v577 = (std::string *)v1048._Mypair._Myval2._Bx._Ptr;
        if ( v1048._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1048._Mypair._Myval2._Mysize >= 8 )
          {
            v579 = v1048._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v578 = -2128831035;
            do
            {
              v578 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v578 ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[7]);
              v577 = (std::string *)((char *)v577 + 8);
              v579 -= 8LL;
            }
            while ( v579 != 0 );
          }
          else
          {
            v578 = -2128831035;
          }
          if ( (v1048._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v580 = 0;
            do
              v578 = 16777619 * (v578 ^ (unsigned __int8)v577->_Mypair._Myval2._Bx._Buf[v580++]);
            while ( (v1048._Mypair._Myval2._Mysize & 7) != v580 );
          }
        }
        else
        {
          v578 = -2128831035;
        }
        LODWORD(v560[3].__vftable) = v578;
        *(_QWORD *)&_Args[0].mIgnored = "slider_steps";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v581 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v581) )
          Json::Value::isNumeric(this: v581);
        v582 = Json::Value::isInt(this: v581);
        v583 = 1;
        if ( v582 )
          v583 = Json::Value::asInt(this: v581, defaultValue: 0);
        if ( LODWORD(v560[4].__vftable) != v583 )
        {
          LODWORD(v560[4].__vftable) = v583;
          LOBYTE(v560[5].mOwner) = (v583 >= 2) | (__int64)v560[5].mOwner & 0xFE;
          SliderComponent::_updateSliderFromStepSize(this: (SliderComponent *)v560, stepSize: 0);
        }
        v1037._Mydata = "slider_direction";
        v1037._Mysize = 16;
        BYTE6(v560[3].__vftable) = UIResolvedDef::getAsOrientation(this: v1110, key: &v1037, defaultValue: Vertical);
        *(_QWORD *)&_Args[0].mIgnored = "slider_inverted";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)15;
        v584 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v584) && !Json::Value::isBool(this: v584) )
          Json::Value::isIntegral(this: v584);
        v585 = Json::Value::isIntegral(this: v584) && Json::Value::asBool(this: v584, defaultValue: false);
        HIBYTE(v560[3].__vftable) = v585;
        *(_QWORD *)&_Args[0].mIgnored = "slider_speed";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v586 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v586) )
          Json::Value::isNumeric(this: v586);
        if ( Json::Value::isNumeric(this: v586) )
          *(float *)v587.m128i_i32 = Json::Value::asFloat(this: v586, defaultValue: 0.0);
        else
          v587 = _mm_cvtsi32_si128(0x3F800000u);
        HIDWORD(v560[4].__vftable) = _mm_cvtsi128_si32(v587);
        v1009._Mydata = "slider_timeout";
        v1009._Mysize = 14;
        v588 = (webrtc::internal::RaceCheckerScope *)UIResolvedDef::getValue(this: v1110, key: &v1009, a3: false);
        if ( !Json::Value::isNull(this: v588) )
        {
          if ( ((__int64)v560[5].mOwner & 1) != 0 )
            v589 = _mm_cvtsi32_si128(0x3E800000u);
          else
            v589 = 0;
          *(_QWORD *)&_Args[0].mIgnored = "slider_timeout";
          _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)14;
          v590 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
          if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v590) )
            Json::Value::isNumeric(this: v590);
          if ( Json::Value::isNumeric(this: v590) )
          {
            *(float *)v591.m128i_i32 = Json::Value::asFloat(this: v590, defaultValue: 0.0);
            v589 = v591;
          }
          LODWORD(v560[4].mOwner) = _mm_cvtsi128_si32(v589);
          BYTE4(v560[4].mOwner) = 1;
        }
        v1010._Mydata = u;
        v1010._Mysize = 0;
        v1011._Mydata = "slider_collection_name";
        v1011._Mysize = 22;
        v592 = _Args;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)_Args, key: &v1011, defaultValue: &v1010);
        v594 = (UIComponent_vtbl *)&v560[6];
        if ( &v560[6] != (UIComponent *)_Args )
        {
          v595 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
            v592 = *(UIResolvedDef **)&_Args[0].mIgnored;
          v596 = (unsigned __int64)v560[7].mOwner;
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v596 )
          {
            if ( v596 >= 0x10 )
              v594 = v560[6].__vftable;
            v560[7].__vftable = *(UIComponent_vtbl **)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
            memmove_0(a1: v594, Src: v592, Size: v595);
            *((_BYTE *)&v594->dtr_UIComponent + v595) = 0;
          }
          else
          {
            ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
              this: (std::string *)&v560[6],
              _New_size: *(const unsigned __int64 *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8],
              _Fn: v593,
              _Args: (const char *)&v592->mIgnored);
          }
        }
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v597 = *(void **)&_Args[0].mIgnored;
          v598 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v598 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
            v597 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
          }
          operator delete(block: v597, __formal: v598);
        }
        v1012._Mydata = (const char *)&Util::EMPTY_STRING;
        v1012._Mysize = 0;
        v1013._Mydata = "tts_value_changed";
        v1013._Mysize = 17;
        v599 = _Args;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)_Args, key: &v1013, defaultValue: &v1012);
        v601 = (UIControl *)&v560[14].mOwner;
        if ( &v560[14].mOwner != (UIControl **)_Args )
        {
          v602 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
            v599 = *(UIResolvedDef **)&_Args[0].mIgnored;
          v603 = (unsigned __int64)v560[16].__vftable;
          if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v603 )
          {
            if ( v603 >= 0x10 )
              v601 = v560[14].mOwner;
            v560[15].mOwner = *(UIControl **)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
            memmove_0(a1: v601, Src: v599, Size: v602);
            *((_BYTE *)&v601->_Wptr._Ptr + v602) = 0;
          }
          else
          {
            ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
              this: (std::string *)&v560[14].mOwner,
              _New_size: *(const unsigned __int64 *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8],
              _Fn: v600,
              _Args: (const char *)&v599->mIgnored);
          }
        }
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v604 = *(void **)&_Args[0].mIgnored;
          v605 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v605 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
            v604 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
          }
          operator delete(block: v604, __formal: v605);
        }
        v1014._Mydata = u;
        v1014._Mysize = 0;
        v1015._Mydata = "slider_name";
        v1015._Mysize = 11;
        v606 = &v1049;
        UIResolvedDef::getAsString(this: v1110, result: &v1049, key: &v1015, defaultValue: &v1014);
        if ( v1049._Mypair._Myval2._Myres >= 0x10 )
          v606 = (std::string *)v1049._Mypair._Myval2._Bx._Ptr;
        if ( v1049._Mypair._Myval2._Mysize != 0 )
        {
          if ( v1049._Mypair._Myval2._Mysize >= 8 )
          {
            v608 = v1049._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
            v607 = -2128831035;
            do
            {
              v607 = 16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619
                               * ((16777619 * (v607 ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[0]))
                                ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[1]))
                              ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[2]))
                            ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[3]))
                          ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[4]))
                        ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[5]))
                      ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[6]))
                    ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[7]);
              v606 = (std::string *)((char *)v606 + 8);
              v608 -= 8LL;
            }
            while ( v608 != 0 );
          }
          else
          {
            v607 = -2128831035;
          }
          if ( (v1049._Mypair._Myval2._Mysize & 7) != 0 )
          {
            v609 = 0;
            do
              v607 = 16777619 * (v607 ^ (unsigned __int8)v606->_Mypair._Myval2._Bx._Buf[v609++]);
            while ( (v1049._Mypair._Myval2._Mysize & 7) != v609 );
          }
        }
        else
        {
          v607 = -2128831035;
        }
        HIDWORD(v560[5].mOwner) = v607;
        *(_QWORD *)&_Args[0].mIgnored = "slider_select_on_hover";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)22;
        v610 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v610) && !Json::Value::isBool(this: v610) )
          Json::Value::isIntegral(this: v610);
        if ( Json::Value::isIntegral(this: v610) )
          v611 = 4 * Json::Value::asBool(this: v610, defaultValue: false);
        else
          v611 = 0;
        LOBYTE(v560[5].mOwner) = v611 | (__int64)v560[5].mOwner & 0xFB;
        *(_QWORD *)&_Args[0].mIgnored = off_14E8D7060;
        _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
        v1016._Mydata = u;
        v1016._Mysize = 0;
        v1017._Mydata = "slider_box_control";
        v1017._Mysize = 18;
        v1095 = 1;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)&v1079, key: &v1017, defaultValue: &v1016);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1079,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v612 = *(void **)&v1079.mIgnored;
          v613 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v613 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v612 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v612, __formal: v613);
        }
        *(_QWORD *)&v1079.mIgnored = off_14E8D7090;
        v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
        v1018._Mydata = u;
        v1018._Mysize = 0;
        v1019._Mydata = "default_control";
        v1019._Mysize = 15;
        v1094 = 1;
        UIResolvedDef::getAsString(this: v1110, result: (std::string *)&defaultValue, key: &v1019, defaultValue: &v1018);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&defaultValue,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
        {
          v614 = *(void **)&defaultValue.mFileSystem;
          v615 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
          if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v615 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
            v614 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
          }
          operator delete(block: v614, __formal: v615);
        }
        *(_QWORD *)&defaultValue.mFileSystem = off_14E8D70C0;
        v1078 = &defaultValue;
        v1020._Mydata = u;
        v1020._Mysize = 0;
        v1021._Mydata = "hover_control";
        v1021._Mysize = 13;
        v1093 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &Src, key: &v1021, defaultValue: &v1020);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&Src,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( Src._Mypair._Myval2._Myres >= 0x10 )
        {
          v616 = Src._Mypair._Myval2._Bx._Ptr;
          v617 = Src._Mypair._Myval2._Myres + 1;
          if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v617 = Src._Mypair._Myval2._Myres + 40;
            v616 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v616, __formal: v617);
        }
        Src._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D70F0;
        p_Src = &Src;
        v1022._Mydata = u;
        v1022._Mysize = 0;
        v1023._Mydata = "background_control";
        v1023._Mysize = 18;
        v1092 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &v1106, key: &v1023, defaultValue: &v1022);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1106,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1106._Mypair._Myval2._Myres >= 0x10 )
        {
          v618 = v1106._Mypair._Myval2._Bx._Ptr;
          v619 = v1106._Mypair._Myval2._Myres + 1;
          if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v619 = v1106._Mypair._Myval2._Myres + 40;
            v618 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v618, __formal: v619);
        }
        v1106._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7120;
        v1107 = &v1106;
        v1024._Mydata = u;
        v1024._Mysize = 0;
        v1025._Mydata = "background_hover_control";
        v1025._Mysize = 24;
        v1091 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &v1069, key: &v1025, defaultValue: &v1024);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1069,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1069._Mypair._Myval2._Myres >= 0x10 )
        {
          v620 = v1069._Mypair._Myval2._Bx._Ptr;
          v621 = v1069._Mypair._Myval2._Myres + 1;
          if ( v1069._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1069._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1069._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v621 = v1069._Mypair._Myval2._Myres + 40;
            v620 = *((char **)v1069._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v620, __formal: v621);
        }
        v1069._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7150;
        v1070 = &v1069;
        v1026._Mydata = u;
        v1026._Mysize = 0;
        v1027._Mydata = "progress_control";
        v1027._Mysize = 16;
        v1090 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &__formal, key: &v1027, defaultValue: &v1026);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&__formal,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( __formal._Mypair._Myval2._Myres >= 0x10 )
        {
          v622 = __formal._Mypair._Myval2._Bx._Ptr;
          v623 = __formal._Mypair._Myval2._Myres + 1;
          if ( __formal._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&__formal._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)__formal._Mypair._Myval2._Bx._Ptr - 1)
                                                                    - 8] >= 0x20 )
              goto LABEL_1922;
            v623 = __formal._Mypair._Myval2._Myres + 40;
            v622 = *((char **)__formal._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v622, __formal: v623);
        }
        __formal._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7180;
        v1051 = &__formal;
        v1028._Mydata = u;
        v1028._Mysize = 0;
        v1029._Mydata = "progress_hover_control";
        v1029._Mysize = 22;
        v1089 = 1;
        UIResolvedDef::getAsString(this: v1110, result: &v1046, key: &v1029, defaultValue: &v1028);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1046,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1046._Mypair._Myval2._Myres >= 0x10 )
        {
          v624 = v1046._Mypair._Myval2._Bx._Ptr;
          v625 = v1046._Mypair._Myval2._Myres + 1;
          if ( v1046._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1046._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1046._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v625 = v1046._Mypair._Myval2._Myres + 40;
            v624 = *((char **)v1046._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v624, __formal: v625);
        }
        if ( v1049._Mypair._Myval2._Myres >= 0x10 )
        {
          v626 = v1049._Mypair._Myval2._Bx._Ptr;
          v627 = v1049._Mypair._Myval2._Myres + 1;
          if ( v1049._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1049._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1049._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v627 = v1049._Mypair._Myval2._Myres + 40;
            v626 = *((char **)v1049._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v626, __formal: v627);
        }
        if ( v1048._Mypair._Myval2._Myres >= 0x10 )
        {
          v628 = v1048._Mypair._Myval2._Bx._Ptr;
          v629 = v1048._Mypair._Myval2._Myres + 1;
          if ( v1048._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1048._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1048._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v629 = v1048._Mypair._Myval2._Myres + 40;
            v628 = *((char **)v1048._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v628, __formal: v629);
        }
        if ( v1068._Mypair._Myval2._Myres >= 0x10 )
        {
          v630 = v1068._Mypair._Myval2._Bx._Ptr;
          v631 = v1068._Mypair._Myval2._Myres + 1;
          if ( v1068._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1068._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1068._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v631 = v1068._Mypair._Myval2._Myres + 40;
            v630 = *((char **)v1068._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v630, __formal: v631);
        }
        if ( v1072._Mypair._Myval2._Myres >= 0x10 )
        {
          v632 = v1072._Mypair._Myval2._Bx._Ptr;
          v633 = v1072._Mypair._Myval2._Myres + 1;
          if ( v1072._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1072._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1072._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v633 = v1072._Mypair._Myval2._Myres + 40;
            v632 = *((char **)v1072._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v632, __formal: v633);
        }
        if ( v1073._Mypair._Myval2._Myres >= 0x10 )
        {
          v634 = v1073._Mypair._Myval2._Bx._Ptr;
          v635 = v1073._Mypair._Myval2._Myres + 1;
          if ( v1073._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1073._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1073._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v635 = v1073._Mypair._Myval2._Myres + 40;
            v634 = *((char **)v1073._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v634, __formal: v635);
        }
        if ( v1076._Mypair._Myval2._Myres >= 0x10 )
        {
          v636 = v1076._Mypair._Myval2._Bx._Ptr;
          v637 = v1076._Mypair._Myval2._Myres + 1;
          if ( v1076._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1076._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1076._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v637 = v1076._Mypair._Myval2._Myres + 40;
            v636 = *((char **)v1076._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v636, __formal: v637);
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1108);
        v638 = (UIControl *)v1110;
        v43 = ownerControl;
        UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v1110);
        UIControlFactory::_populateSoundComponent(def, ownerControl: v638, a3: (bool)v43);
        UIControlFactory::_populateTextToSpeechComponent(
          def: (const UIResolvedDef *)v638,
          ownerControl: v43,
          controlPriorityDefault: 1000);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v46;
      v294 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v47[23]._Mypair._Myval2 + (unsigned int)(8 * v51));
      v295 = v47[24]._Mypair._Myval2;
      if ( v295 == v47[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v47 + 23,
          _Val: v294);
        v380 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v295 == (StructureFeature *)v294 )
        {
          v295->__vftable = (StructureFeature_vtbl *)v46;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_840:
          ownerControl->mComponentsInUse |= v48;
          goto LABEL_841;
        }
        v296 = (std::unique_ptr<RuinedPortalFeature> *)&v295[-1].mActiveBlueprintCreateCount;
        v297 = *(StructureFeature_vtbl **)&v295[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v295[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v295->__vftable = v297;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v296 != v294 )
        {
          v298 = v296[-1]._Mypair._Myval2;
          v299 = v296->_Mypair._Myval2;
          v296[-1]._Mypair._Myval2 = nullptr;
          v296->_Mypair._Myval2 = v298;
          if ( v299 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v299->dtr_StructureFeature)(a1: v299, a2: 1);
          --v296;
        }
        v380 = v294->_Mypair._Myval2;
        v294->_Mypair._Myval2 = (RuinedPortalFeature *)v46;
      }
      if ( v380 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v380->dtr_StructureFeature)(a1: v380, a2: 1);
      goto LABEL_840;
    case 17LL:
      v163 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateInputComponent(def, ownerControl: v163);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v163);
      LOBYTE(v164) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v164);
      v165 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 104);
      if ( v165 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x68u, alignment: 0);
      v166 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v165 + 1) = ownerControl;
      *(_QWORD *)v165 = &off_14E8D60B0;
      *((_WORD *)v165 + 8) = 0;
      *(_OWORD *)(v165 + 24) = 0;
      *(_OWORD *)(v165 + 40) = 0;
      *(_OWORD *)(v165 + 56) = 0;
      *(_OWORD *)(v165 + 72) = 0;
      *(_OWORD *)(v165 + 88) = 0;
      if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderBoxComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderBoxComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VSliderBoxComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                          (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                          1u);
          `uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VSliderBoxComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v167 = `uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId;
      v168 = v166[22]._Mypair._Myval2;
      v169 = (((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1))
            - ((((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1)) >> 1)
             & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v170 = (0x101010101010101LL
            * ((v169
              + (((((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1))
                 - ((((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1)) >> 1)
                  & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v169
                + (((((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1))
                   - ((((unsigned __int64)v168 & (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId - 1)) >> 1)
                    & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v171 = v166 + 23;
      if ( (`uicontrol_id<UIComponent,SliderBoxComponent>'::`2'::id.mBitId & (unsigned __int64)v168) != 0 )
      {
        v172 = *((RenderableComponent **)&v171->_Mypair._Myval2->__vftable + v170);
        v1058 = v165;
        v173 = guard_dispatch_icall_nop(a1: v172);
        v1058 = v165;
        v174 = guard_dispatch_icall_nop(a1: v172);
        if ( (v174 | v173) == 1 )
        {
          if ( v173 != 0 )
          {
            v175 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v176 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v175 != v176 )
            {
              while ( *v175 != v172 )
              {
                if ( ++v175 == v176 )
                  goto LABEL_464;
              }
            }
            if ( v175 != v176 )
            {
              v400 = v174;
              memmove_0(a1: v175, Src: v175 + 1, Size: (char *)v176 - (char *)(v175 + 1));
              v174 = v400;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_464:
          if ( v174 != 0 )
          {
            v401 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v402 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v401 != v402 )
            {
              while ( *v401 != (CustomFrameUpdateComponent *)v172 )
              {
                if ( ++v401 == v402 )
                  goto LABEL_471;
              }
            }
            if ( v401 != v402 )
            {
              memmove_0(a1: v401, Src: v401 + 1, Size: (char *)v402 - (char *)(v401 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_471:
        v403 = *((void (__fastcall ****)(_QWORD, __int64))&v171->_Mypair._Myval2->__vftable + v170);
        *((_QWORD *)&v171->_Mypair._Myval2->__vftable + v170) = v165;
        if ( v403 != nullptr )
          (**v403)(a1: v403, a2: 1);
LABEL_810:
        v1058 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v165) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v165;
          v540 = ownerControl;
          v541 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v541 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1058 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v541);
          }
          else
          {
            *v541 = (RenderableComponent *)v165;
            ++v540->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1058 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v165) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v165;
          v542 = ownerControl;
          v543 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v543 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1058 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v543);
          }
          else
          {
            *v543 = (CustomFrameUpdateComponent *)v165;
            ++v542->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        *(_QWORD *)&_Args[0].mIgnored = off_14E8D71B0;
        _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
        v1069._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 0;
        __formal._Mypair._Myval2._Bx._Ptr = "default_control";
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 15;
        v1088 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&__formal,
          defaultValue: (std::string_view *)&v1069);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1079,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v544 = *(void **)&v1079.mIgnored;
          v545 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v545 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v544 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v544, __formal: v545);
        }
        *(_QWORD *)&v1079.mIgnored = off_14E8D71E0;
        v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
        v1076._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 0;
        v1073._Mypair._Myval2._Bx._Ptr = "hover_control";
        *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 13;
        v1087 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&defaultValue,
          key: (std::string_view *)&v1073,
          defaultValue: (std::string_view *)&v1076);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&defaultValue,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
        {
          v546 = *(void **)&defaultValue.mFileSystem;
          v547 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
          if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                  - 8LL
                                  - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v547 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
            v546 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
          }
          operator delete(block: v546, __formal: v547);
        }
        *(_QWORD *)&defaultValue.mFileSystem = off_14E8D7210;
        v1078 = &defaultValue;
        v1072._Mypair._Myval2._Bx = (std::_String_val<std::_Simple_types<char> >::_Bxty)(unsigned __int64)u;
        v1068._Mypair._Myval2._Bx._Ptr = "locked_control";
        *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 14;
        v1086 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &Src,
          key: (std::string_view *)&v1068,
          defaultValue: (std::string_view *)&v1072);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&Src,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( Src._Mypair._Myval2._Myres >= 0x10 )
        {
          v548 = Src._Mypair._Myval2._Bx._Ptr;
          v549 = Src._Mypair._Myval2._Myres + 1;
          if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v549 = Src._Mypair._Myval2._Myres + 40;
            v548 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v548, __formal: v549);
        }
        Src._Mypair._Myval2._Bx._Ptr = (char *)off_14E8D7240;
        p_Src = &Src;
        v1048._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 0;
        v1049._Mypair._Myval2._Bx._Ptr = "indent_control";
        *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 14;
        v1085 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: &v1106,
          key: (std::string_view *)&v1049,
          defaultValue: (std::string_view *)&v1048);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1106,
          setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)1);
        if ( v1106._Mypair._Myval2._Myres >= 0x10 )
        {
          v550 = v1106._Mypair._Myval2._Bx._Ptr;
          v551 = v1106._Mypair._Myval2._Myres + 1;
          if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
              goto LABEL_1922;
            v551 = v1106._Mypair._Myval2._Myres + 40;
            v550 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
          }
          operator delete(block: v550, __formal: v551);
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)v1108);
        v43 = ownerControl;
        UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v1110);
        goto LABEL_1734;
      }
      *(_QWORD *)&_Args[0].mIgnored = v165;
      v288 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v166[23]._Mypair._Myval2 + (unsigned int)(8 * v170));
      v289 = v166[24]._Mypair._Myval2;
      if ( v289 == v166[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v166 + 23,
          _Val: v288);
        v379 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v289 == (StructureFeature *)v288 )
        {
          v289->__vftable = (StructureFeature_vtbl *)v165;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_809:
          ownerControl->mComponentsInUse |= v167;
          goto LABEL_810;
        }
        v290 = (std::unique_ptr<RuinedPortalFeature> *)&v289[-1].mActiveBlueprintCreateCount;
        v291 = *(StructureFeature_vtbl **)&v289[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v289[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v289->__vftable = v291;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v290 != v288 )
        {
          v292 = v290[-1]._Mypair._Myval2;
          v293 = v290->_Mypair._Myval2;
          v290[-1]._Mypair._Myval2 = nullptr;
          v290->_Mypair._Myval2 = v292;
          if ( v293 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v293->dtr_StructureFeature)(a1: v293, a2: 1);
          --v290;
        }
        v379 = v288->_Mypair._Myval2;
        v288->_Mypair._Myval2 = (RuinedPortalFeature *)v165;
      }
      if ( v379 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v379->dtr_StructureFeature)(a1: v379, a2: 1);
      goto LABEL_809;
    case 18LL:
      v223 = v1110;
      v224 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateCollectionComponent(def: v223, ownerControl: v224);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: (UIControl *)v223);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: (UIControl *)v223);
      LOBYTE(v225) = 27;
      LOBYTE(def) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                      a2: (Memory::MemoryCategory)v225);
      v226 = (RenderableComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                      a2: 32);
      if ( v226 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x20u, alignment: 0);
      v227 = (std::unique_ptr<StructureFeature> *)ownerControl;
      v226->mOwner = ownerControl;
      v226->__vftable = (RenderableComponent_vtbl *)&off_14E8D6340;
      v226->mSupportsLayoutOverride = true;
      v226->mMeasuredSize.x = 0.0;
      LOWORD(v226->mMeasuredSize.y) = 0;
      if ( __TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                           (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                           1u);
          `uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v228 = `uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId;
      v229 = v227[22]._Mypair._Myval2;
      v230 = (((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1))
            - ((((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1)) >> 1)
             & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v231 = (0x101010101010101LL
            * ((v230
              + (((((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1))
                 - ((((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1)) >> 1)
                  & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v230
                + (((((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1))
                   - ((((unsigned __int64)v229 & (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1)) >> 1)
                    & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v232 = v227 + 23;
      if ( (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId & (unsigned __int64)v229) != 0 )
      {
        v233 = *((RenderableComponent **)&v232->_Mypair._Myval2->__vftable + v231);
        v1057 = v226;
        v234 = guard_dispatch_icall_nop(a1: v233);
        v1057 = v226;
        v235 = guard_dispatch_icall_nop(a1: v233);
        if ( (v235 | v234) == 1 )
        {
          if ( v234 != 0 )
          {
            v236 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v237 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v236 != v237 )
            {
              while ( *v236 != v233 )
              {
                if ( ++v236 == v237 )
                  goto LABEL_508;
              }
            }
            if ( v236 != v237 )
            {
              v416 = v235;
              memmove_0(a1: v236, Src: v236 + 1, Size: (char *)v237 - (char *)(v236 + 1));
              v235 = v416;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_508:
          if ( v235 != 0 )
          {
            v417 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v418 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v417 != v418 )
            {
              while ( *v417 != (CustomFrameUpdateComponent *)v233 )
              {
                if ( ++v417 == v418 )
                  goto LABEL_515;
              }
            }
            if ( v417 != v418 )
            {
              memmove_0(a1: v417, Src: v417 + 1, Size: (char *)v418 - (char *)(v417 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_515:
        v419 = *((void (__fastcall ****)(_QWORD, __int64))&v232->_Mypair._Myval2->__vftable + v231);
        *((_QWORD *)&v232->_Mypair._Myval2->__vftable + v231) = v226;
        if ( v419 != nullptr )
          (**v419)(a1: v419, a2: 1);
LABEL_1192:
        v1057 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v226) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v226;
          v692 = ownerControl;
          v693 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v693 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1057 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v693);
          }
          else
          {
            *v693 = v226;
            ++v692->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1057 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v226) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v226;
          v695 = ownerControl;
          v696 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v696 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1057 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v696);
          }
          else
          {
            *v696 = (CustomFrameUpdateComponent *)v226;
            ++v695->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( __TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          if ( __TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
          {
            `uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                             (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                             1u);
            `uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mID);
            Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VStackPanelComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
          }
        }
        v697 = ownerControl->mComponentsInUse;
        if ( (`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId & v697) != 0
          && (v694 = 1431655765,
              v698 = ((`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1) & v697)
                   - ((((`uicontrol_id<UIComponent,StackPanelComponent>'::`2'::id.mBitId - 1) & v697) >> 1)
                    & 0x5555555555555555LL),
              v699 = (0x101010101010101LL
                    * (((v698 & 0x3333333333333333LL)
                      + ((v698 >> 2) & 0x3333333333333333LL)
                      + (((v698 & 0x3333333333333333LL) + ((v698 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v700 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v700 > v699) )
        {
          v701 = v700[v699]._Mypair._Myval2;
        }
        else
        {
          v701 = nullptr;
        }
        *(_QWORD *)&v1079.mIgnored = "orientation";
        v1079.mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)11;
        LOBYTE(v694) = 1;
        LOBYTE(v701[1].__vftable) = UIResolvedDef::getAsOrientation(
                                      this: v1110,
                                      key: (std::string_view *)&v1079,
                                      defaultValue: v694);
        *(_QWORD *)&_Args[0].mIgnored = "use_child_anchors";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)17;
        v702 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v702) && !Json::Value::isBool(this: v702) )
          Json::Value::isIntegral(this: v702);
        v703 = Json::Value::isIntegral(this: v702) && Json::Value::asBool(this: v702, defaultValue: false);
        LOBYTE(v701[1].mOwner) = v703;
        *(_QWORD *)&_Args[0].mIgnored = "use_priority";
        _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = (char *)12;
        v704 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)_Args, a3: false);
        if ( !Json::Value::isNull(this: (webrtc::internal::RaceCheckerScope *)v704) && !Json::Value::isBool(this: v704) )
          Json::Value::isIntegral(this: v704);
        v705 = Json::Value::isIntegral(this: v704) && Json::Value::asBool(this: v704, defaultValue: false);
        BYTE1(v701[1].mOwner) = v705;
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)def);
        goto LABEL_1733;
      }
      *(_QWORD *)&_Args[0].mIgnored = v226;
      v312 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v227[23]._Mypair._Myval2 + (unsigned int)(8 * v231));
      v313 = v227[24]._Mypair._Myval2;
      if ( v313 == v227[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v227 + 23,
          _Val: v312);
        v383 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v313 == (StructureFeature *)v312 )
        {
          v313->__vftable = (StructureFeature_vtbl *)v226;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1191:
          ownerControl->mComponentsInUse |= v228;
          goto LABEL_1192;
        }
        v314 = (std::unique_ptr<RuinedPortalFeature> *)&v313[-1].mActiveBlueprintCreateCount;
        v315 = *(StructureFeature_vtbl **)&v313[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v313[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v313->__vftable = v315;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v314 != v312 )
        {
          v316 = v314[-1]._Mypair._Myval2;
          v317 = v314->_Mypair._Myval2;
          v314[-1]._Mypair._Myval2 = nullptr;
          v314->_Mypair._Myval2 = v316;
          if ( v317 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v317->dtr_StructureFeature)(a1: v317, a2: 1);
          --v314;
        }
        v383 = v312->_Mypair._Myval2;
        v312->_Mypair._Myval2 = (RuinedPortalFeature *)v226;
      }
      if ( v383 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v383->dtr_StructureFeature)(a1: v383, a2: 1);
      goto LABEL_1191;
    case 19LL:
      v254 = (UIControl *)v1110;
      v43 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v254);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v254);
      UIControlFactory::_populateInputComponent(def, ownerControl: v254);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v254);
      UIControlFactory::_populateSoundComponent(def, ownerControl: v254, a3: (bool)v43);
      UIControlFactory::_populateToggleComponent(def: (const UIResolvedDef *)v254, ownerControl: v43);
      UIControlFactory::_populateTextToSpeechComponent(
        def: (const UIResolvedDef *)v254,
        ownerControl: v43,
        controlPriorityDefault: 1000);
      goto LABEL_1734;
    case 20LL:
      v177 = (UIControl *)v1110;
      v178 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v177);
      UIControlFactory::_populateInputComponent(def, ownerControl: v177);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v177);
      UIControlFactory::_populateSpriteComponent(def, ownerControl: v177);
      LOBYTE(v179) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v179);
      UIControlFactory::_populatePageIndicatorManagerComponent(def: (const UIResolvedDef *)v177, ownerControl: v178);
      v180 = (RenderableComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                      a2: 72);
      if ( v180 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x48u, alignment: 0);
      v181 = (std::unique_ptr<StructureFeature> *)ownerControl;
      v180->mOwner = ownerControl;
      *(_OWORD *)&v180->mSupportsLayoutOverride = 0;
      v180[1].UIComponent = 0;
      v180->__vftable = (RenderableComponent_vtbl *)&ImageCyclingComponent::`vftable';
      *(_OWORD *)&v180[1].mSupportsLayoutOverride = 0;
      v180[2].__vftable = nullptr;
      if ( dword_151E0C988 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C988);
        if ( dword_151E0C988 == -1 )
        {
          qword_151E0C980 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C988);
        }
      }
      v182 = qword_151E0C980;
      v183 = v181[22]._Mypair._Myval2;
      v184 = (((unsigned __int64)v183 & (qword_151E0C980 - 1))
            - ((((unsigned __int64)v183 & (qword_151E0C980 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v185 = (0x101010101010101LL
            * ((v184
              + (((((unsigned __int64)v183 & (qword_151E0C980 - 1))
                 - ((((unsigned __int64)v183 & (qword_151E0C980 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v184
                + (((((unsigned __int64)v183 & (qword_151E0C980 - 1))
                   - ((((unsigned __int64)v183 & (qword_151E0C980 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v186 = v181 + 23;
      if ( (qword_151E0C980 & (unsigned __int64)v183) != 0 )
      {
        v187 = *((RenderableComponent **)&v186->_Mypair._Myval2->__vftable + v185);
        v1055 = v180;
        v188 = guard_dispatch_icall_nop(a1: v187);
        v1055 = v180;
        v189 = guard_dispatch_icall_nop(a1: v187);
        if ( (v189 | v188) == 1 )
        {
          if ( v188 != 0 )
          {
            v190 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v191 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v190 != v191 )
            {
              while ( *v190 != v187 )
              {
                if ( ++v190 == v191 )
                  goto LABEL_552;
              }
            }
            if ( v190 != v191 )
            {
              v432 = v189;
              memmove_0(a1: v190, Src: v190 + 1, Size: (char *)v191 - (char *)(v190 + 1));
              v189 = v432;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_552:
          if ( v189 != 0 )
          {
            v433 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v434 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v433 != v434 )
            {
              while ( *v433 != (CustomFrameUpdateComponent *)v187 )
              {
                if ( ++v433 == v434 )
                  goto LABEL_559;
              }
            }
            if ( v433 != v434 )
            {
              memmove_0(a1: v433, Src: v433 + 1, Size: (char *)v434 - (char *)(v433 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_559:
        v435 = *((void (__fastcall ****)(_QWORD, __int64))&v186->_Mypair._Myval2->__vftable + v185);
        *((_QWORD *)&v186->_Mypair._Myval2->__vftable + v185) = v180;
        if ( v435 != nullptr )
          (**v435)(a1: v435, a2: 1);
LABEL_1448:
        v1055 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v180) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v180;
          v802 = ownerControl;
          v803 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v803 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1055 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v803);
          }
          else
          {
            *v803 = v180;
            ++v802->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1055 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v180) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v180;
          v804 = ownerControl;
          v805 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v805 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1055 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v805);
          }
          else
          {
            *v805 = (CustomFrameUpdateComponent *)v180;
            ++v804->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( dword_151E0C988 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &dword_151E0C988);
          if ( dword_151E0C988 == -1 )
          {
            qword_151E0C980 = 1LL << _InterlockedExchangeAdd64(
                                       (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                       1u);
            Init_thread_footer(pOnce: &dword_151E0C988);
          }
        }
        v806 = ownerControl->mComponentsInUse;
        if ( (qword_151E0C980 & v806) != 0
          && (v807 = ((qword_151E0C980 - 1) & v806) - ((((qword_151E0C980 - 1) & v806) >> 1) & 0x5555555555555555LL),
              v808 = (0x101010101010101LL
                    * (((v807 & 0x3333333333333333LL)
                      + ((v807 >> 2) & 0x3333333333333333LL)
                      + (((v807 & 0x3333333333333333LL) + ((v807 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v809 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v809 > v808) )
        {
          v1080 = v809[v808]._Mypair._Myval2;
        }
        else
        {
          v1080 = nullptr;
        }
        __formal._Mypair._Myval2._Bx._Ptr = "images";
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 6;
        v810 = UIResolvedDef::getValue(this: v1110, key: (std::string_view *)&__formal, a3: false);
        if ( !Json::Value::isArray(this: v810) )
          ContentLogHelper::_contentLog<char const (&)[185]>(
            level: true,
            area: (const LogLevel)3,
            args: UI,
            a4: (const char (*)[150])"JSON UI parse failure: Must define 'images' as an array!");
        if ( Json::Value::isArray(this: v810) )
        {
          memset(&v1069, 0, 24);
          Json::Value::begin(this: v810, result: (Json::ValueConstIterator *)&v1076);
          Json::Value::end(this: v810, result: (Json::ValueConstIterator *)&v1073);
          def = (UIResolvedDef *)((char *)def + 120);
          if ( !Json::ValueIteratorBase::isEqual(
                  this: (Json::ValueIteratorBase *)&v1076,
                  other: (const Json::ValueIteratorBase *)&v1073) )
          {
            v815 = Json::ValueIteratorBase::deref(this: (Json::ValueIteratorBase *)&v1076);
            if ( Json::Value::isObject(this: v815) )
            {
              *(_QWORD *)&_Args[0].mIgnored = u;
              _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr = nullptr;
              *(_QWORD *)&defaultValue.mFileSystem = u;
              defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = nullptr;
              UIResolvedDef::UIResolvedDef(
                this: &v1079,
                variablesStack: (std::vector<Json::Value *> *)def,
                defNamespace: (std::string_view *)&defaultValue,
                defName: (std::string_view *)_Args,
                a5: v815,
                a6: v815);
              if ( !v1079.mIgnored )
              {
                v1072._Mypair._Myval2._Bx._Ptr = (char *)u;
                *(_QWORD *)&v1072._Mypair._Myval2._Bx._Alias[8] = 0;
                v1068._Mypair._Myval2._Bx._Ptr = "texture_path";
                *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 12;
                UIResolvedDef::getAsString(
                  this: &v1079,
                  result: &Src,
                  key: (std::string_view *)&v1068,
                  defaultValue: (std::string_view *)&v1072);
                if ( Src._Mypair._Myval2._Mysize != 0 )
                {
                  v1048._Mypair._Myval2._Bx._Ptr = "InUserPackage";
                  *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 13;
                  v1049._Mypair._Myval2._Bx._Ptr = "texture_file_system";
                  *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 19;
                  v816 = &v1106;
                  UIResolvedDef::getAsString(
                    this: &v1079,
                    result: &v1106,
                    key: (std::string_view *)&v1049,
                    defaultValue: (std::string_view *)&v1048);
                  if ( v1106._Mypair._Myval2._Myres >= 0x10 )
                    v816 = (std::string *)v1106._Mypair._Myval2._Bx._Ptr;
                  v1046._Mypair._Myval2._Bx._Ptr = (char *)v816;
                  *(_QWORD *)&v1046._Mypair._Myval2._Bx._Alias[8] = v1106._Mypair._Myval2._Mysize;
                  v817 = ResourceUtil::pathFromString(name: (std::string_view *)&v1046);
                  v818 = Src._Mypair._Myval2._Myres;
                  v819 = (std::string *)Src._Mypair._Myval2._Bx._Ptr;
                  v820 = Src._Mypair._Myval2._Mysize;
                  v528 = (CustomRenderComponent *)_Args;
                  memset_0(a1: _Args, Val: 0, Size: 0x408u);
                  if ( v820 <= 0x3FF )
                  {
                    if ( v818 < 0x10 )
                      v819 = &Src;
                    memcpy_0(a1: _Args, Src: v819, Size: v820);
                    v1039 = v820;
                    *(&_Args[0].mIgnored + v820) = false;
                    v821 = v1039;
                  }
                  else
                  {
                    v821 = 0;
                  }
                  v1071._Mydata = (const char *)_Args;
                  v1071._Mysize = v821;
                  ResourceLocation::ResourceLocation(
                    this: &defaultValue,
                    path: (Core::PathView *)&v1071,
                    fileSystem: v817);
                  v822 = *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8];
                  if ( *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] == v1069._Mypair._Myval2._Mysize )
                  {
                    std::vector<ResourceLocation>::_Emplace_reallocate<ResourceLocation>(
                      this: (std::vector<ResourceLocation> *)&v1069,
                      _Whereptr: *(ResourceLocation **)&v1069._Mypair._Myval2._Bx._Alias[8],
                      _Val: &defaultValue);
                  }
                  else
                  {
                    **(_DWORD **)&v1069._Mypair._Myval2._Bx._Alias[8] = defaultValue.mFileSystem;
                    *(_OWORD *)(v822 + 8) = 0;
                    *(_OWORD *)(v822 + 24) = 0;
                    p_mPath = &defaultValue.mPath;
                    if ( defaultValue.mPath.mContainer._Mypair._Myval2._Myres >= 0x10 )
                      p_mPath = (Core::PathBuffer<std::string > *)defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr;
                    v823 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize;
                    if ( (defaultValue.mPath.mContainer._Mypair._Myval2._Mysize & 0x8000000000000000uLL) != 0LL )
                      std::_Xlen_string();
                    if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize > 0xF )
                    {
                      v824 = 22;
                      if ( (defaultValue.mPath.mContainer._Mypair._Myval2._Mysize | 0xF) >= 0x17 )
                        v824 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize | 0xF;
                      allocate = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate;
                      if ( (defaultValue.mPath.mContainer._Mypair._Myval2._Mysize | 0xF) < 0xFFF )
                      {
                        v827 = (_QWORD *)allocate(
                                           this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                           a2: v824 + 1);
                        if ( v827 == nullptr )
                        {
                          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: v824 + 1, alignment: 0);
                          goto LABEL_1920;
                        }
                      }
                      else
                      {
                        v826 = (__int64)allocate(
                                          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                          a2: v824 + 40);
                        if ( v826 == 0 )
                          `anonymous namespace'::MemoryAnon::reportBadAlloc(size: v824 + 40, alignment: 0);
                        v827 = (_QWORD *)((v826 + 39) & 0xFFFFFFFFFFFFFFE0uLL);
                        *(v827 - 1) = v826;
                      }
                      *(_QWORD *)(v822 + 8) = v827;
                      *(_QWORD *)(v822 + 24) = v823;
                      *(_QWORD *)(v822 + 32) = v824;
                      memcpy_0(a1: v827, Src: p_mPath, Size: v823 + 1);
                    }
                    else
                    {
                      *(_QWORD *)(v822 + 24) = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize;
                      *(_QWORD *)(v822 + 32) = 15;
                      *(__m128i *)(v822 + 8) = _mm_loadu_si128((const __m128i *)p_mPath);
                    }
                    *(__m128i *)(v822 + 40) = _mm_loadu_si128((const __m128i *)&defaultValue.mPathHash);
                    *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] += 56LL;
                  }
                  if ( defaultValue.mPath.mContainer._Mypair._Myval2._Myres >= 0x10 )
                  {
                    v828 = defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr;
                    v829 = defaultValue.mPath.mContainer._Mypair._Myval2._Myres + 1;
                    if ( defaultValue.mPath.mContainer._Mypair._Myval2._Myres + 1 >= 0x1000 )
                    {
                      if ( (unsigned __int64)&defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
                        goto LABEL_1922;
                      v829 = defaultValue.mPath.mContainer._Mypair._Myval2._Myres + 40;
                      v828 = *((char **)defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr - 1);
                    }
                    operator delete(block: v828, __formal: v829);
                  }
                  if ( v1106._Mypair._Myval2._Myres >= 0x10 )
                  {
                    v830 = v1106._Mypair._Myval2._Bx._Ptr;
                    v831 = v1106._Mypair._Myval2._Myres + 1;
                    if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
                    {
                      if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr
                                                                              - 1)
                                                                           - 8] >= 0x20 )
                        goto LABEL_1922;
                      v831 = v1106._Mypair._Myval2._Myres + 40;
                      v830 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
                    }
                    operator delete(block: v830, __formal: v831);
                  }
                }
                if ( Src._Mypair._Myval2._Myres >= 0x10 )
                {
                  v812 = Src._Mypair._Myval2._Bx._Ptr;
                  v811 = Src._Mypair._Myval2._Myres + 1;
                  if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
                  {
                    if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1)
                                                                       - 8] >= 0x20 )
                      goto LABEL_1922;
                    v811 = Src._Mypair._Myval2._Myres + 40;
                    v812 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
                  }
                  operator delete(block: v812, __formal: v811);
                }
              }
              UIResolvedDef::~UIResolvedDef(this: &v1079);
            }
            JUMPOUT(0x14459188FLL);
          }
          webrtc::VideoSinkInterface<webrtc::VideoFrame>::OnConstraintsChanged(__formal: &v1073, __formal: v814);
          webrtc::VideoSinkInterface<webrtc::VideoFrame>::OnConstraintsChanged(__formal: &v1076, __formal: v832);
          v833 = v1080;
          if ( &v1080[3] == (UIComponent *)&v1069 )
          {
            v834 = (char *)v1080[3].__vftable;
            v835 = v1080[3].mOwner;
          }
          else
          {
            std::vector<ResourceLocation>::_Tidy(this: (std::vector<FlatWorldLayer> *)&v1080[3]);
            v833 = v1080;
            v834 = v1069._Mypair._Myval2._Bx._Ptr;
            v1080[3].__vftable = (UIComponent_vtbl *)v1069._Mypair._Myval2._Bx._Ptr;
            v835 = *(UIControl **)&v1069._Mypair._Myval2._Bx._Alias[8];
            v833[3].mOwner = *(UIControl **)&v1069._Mypair._Myval2._Bx._Alias[8];
            v833[4].__vftable = (UIComponent_vtbl *)v1069._Mypair._Myval2._Mysize;
            memset(&v1069, 0, 24);
          }
          v833[1].__vftable = (UIComponent_vtbl *)(0x6DB6DB6DB6DB6DB7LL * (((char *)v835 - v834) >> 3));
          std::vector<ResourceLocation>::_Tidy(this: (std::vector<FlatWorldLayer> *)&v1069);
        }
        goto LABEL_1387;
      }
      *(_QWORD *)&_Args[0].mIgnored = v180;
      v336 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v181[23]._Mypair._Myval2 + (unsigned int)(8 * v185));
      v337 = v181[24]._Mypair._Myval2;
      if ( v337 == v181[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v181 + 23,
          _Val: v336);
        v387 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v337 == (StructureFeature *)v336 )
        {
          v337->__vftable = (StructureFeature_vtbl *)v180;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1447:
          ownerControl->mComponentsInUse |= v182;
          goto LABEL_1448;
        }
        v338 = (std::unique_ptr<RuinedPortalFeature> *)&v337[-1].mActiveBlueprintCreateCount;
        v339 = *(StructureFeature_vtbl **)&v337[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v337[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v337->__vftable = v339;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v338 != v336 )
        {
          v340 = v338[-1]._Mypair._Myval2;
          v341 = v338->_Mypair._Myval2;
          v338[-1]._Mypair._Myval2 = nullptr;
          v338->_Mypair._Myval2 = v340;
          if ( v341 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v341->dtr_StructureFeature)(a1: v341, a2: 1);
          --v338;
        }
        v387 = v336->_Mypair._Myval2;
        v336->_Mypair._Myval2 = (RuinedPortalFeature *)v180;
      }
      if ( v387 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v387->dtr_StructureFeature)(a1: v387, a2: 1);
      goto LABEL_1447;
    case 21LL:
      v193 = (UIControl *)v1110;
      v194 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v193);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v193);
      UIControlFactory::_populateTextComponent(def, ownerControl: v193);
      UIControlFactory::_populateTextToSpeechComponent(
        def: (const UIResolvedDef *)v193,
        ownerControl: v194,
        controlPriorityDefault: 0);
      UIControlFactory::_populateInputComponent(def, ownerControl: v193);
      LOBYTE(v195) = 27;
      LOBYTE(def) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                      a2: (Memory::MemoryCategory)v195);
      UIControlFactory::_populatePageIndicatorManagerComponent(def: (const UIResolvedDef *)v193, ownerControl: v194);
      v196 = (RenderableComponent *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                                      a2: 72);
      if ( v196 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x48u, alignment: 0);
      v197 = (std::unique_ptr<StructureFeature> *)ownerControl;
      v196->mOwner = ownerControl;
      *(_OWORD *)&v196->mSupportsLayoutOverride = 0;
      v196[1].UIComponent = 0;
      v196->__vftable = (RenderableComponent_vtbl *)&off_14E8D6450;
      *(_OWORD *)&v196[1].mSupportsLayoutOverride = 0;
      v196[2].__vftable = nullptr;
      if ( dword_151E0C998 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C998);
        if ( dword_151E0C998 == -1 )
        {
          qword_151E0C990 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C998);
        }
      }
      v198 = qword_151E0C990;
      v199 = v197[22]._Mypair._Myval2;
      v200 = (((unsigned __int64)v199 & (qword_151E0C990 - 1))
            - ((((unsigned __int64)v199 & (qword_151E0C990 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v201 = (0x101010101010101LL
            * ((v200
              + (((((unsigned __int64)v199 & (qword_151E0C990 - 1))
                 - ((((unsigned __int64)v199 & (qword_151E0C990 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v200
                + (((((unsigned __int64)v199 & (qword_151E0C990 - 1))
                   - ((((unsigned __int64)v199 & (qword_151E0C990 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v202 = v197 + 23;
      if ( (qword_151E0C990 & (unsigned __int64)v199) != 0 )
      {
        v203 = *((RenderableComponent **)&v202->_Mypair._Myval2->__vftable + v201);
        v1054 = v196;
        v204 = guard_dispatch_icall_nop(a1: v203);
        v1054 = v196;
        v205 = guard_dispatch_icall_nop(a1: v203);
        if ( (v205 | v204) == 1 )
        {
          if ( v204 != 0 )
          {
            v206 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v207 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v206 != v207 )
            {
              while ( *v206 != v203 )
              {
                if ( ++v206 == v207 )
                  goto LABEL_585;
              }
            }
            if ( v206 != v207 )
            {
              v444 = v205;
              memmove_0(a1: v206, Src: v206 + 1, Size: (char *)v207 - (char *)(v206 + 1));
              v205 = v444;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_585:
          if ( v205 != 0 )
          {
            v445 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v446 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v445 != v446 )
            {
              while ( *v445 != (CustomFrameUpdateComponent *)v203 )
              {
                if ( ++v445 == v446 )
                  goto LABEL_592;
              }
            }
            if ( v445 != v446 )
            {
              memmove_0(a1: v445, Src: v445 + 1, Size: (char *)v446 - (char *)(v445 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_592:
        v447 = *((void (__fastcall ****)(_QWORD, __int64))&v202->_Mypair._Myval2->__vftable + v201);
        *((_QWORD *)&v202->_Mypair._Myval2->__vftable + v201) = v196;
        if ( v447 != nullptr )
          (**v447)(a1: v447, a2: 1);
LABEL_1716:
        v1054 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v196) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v196;
          v916 = ownerControl;
          v917 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v917 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1054 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v917);
          }
          else
          {
            *v917 = v196;
            ++v916->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1054 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v196) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v196;
          v918 = ownerControl;
          v919 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v919 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1054 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v919);
          }
          else
          {
            *v919 = (CustomFrameUpdateComponent *)v196;
            ++v918->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        if ( dword_151E0C998 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &dword_151E0C998);
          if ( dword_151E0C998 == -1 )
          {
            qword_151E0C990 = 1LL << _InterlockedExchangeAdd64(
                                       (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                       1u);
            Init_thread_footer(pOnce: &dword_151E0C998);
          }
        }
        v920 = ownerControl->mComponentsInUse;
        if ( (qword_151E0C990 & v920) != 0
          && (v921 = ((qword_151E0C990 - 1) & v920) - ((((qword_151E0C990 - 1) & v920) >> 1) & 0x5555555555555555LL),
              v922 = (0x101010101010101LL
                    * (((v921 & 0x3333333333333333LL)
                      + ((v921 >> 2) & 0x3333333333333333LL)
                      + (((v921 & 0x3333333333333333LL) + ((v921 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v923 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v923 > v922) )
        {
          v924 = (std::vector<ScriptModuleMinecraft::ScriptItemFilterError> *)v923[v922]._Mypair._Myval2;
        }
        else
        {
          v924 = nullptr;
        }
        memset(&v1079, 0, 24);
        *(_QWORD *)&defaultValue.mFileSystem = "text_labels";
        defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = (char *)11;
        UIResolvedDef::getAsStringVector(
          this: v1110,
          result: (std::vector<std::string> *)_Args,
          key: (std::string_view *)&defaultValue,
          defaultValue: (const std::vector<std::string> *)&v1079);
        std::vector<ScriptModuleMinecraft::ScriptItemFilterError>::_Tidy(this: (std::vector<ScriptModuleMinecraft::ScriptItemFilterError> *)&v1079);
        if ( &v924[2] == (std::vector<ScriptModuleMinecraft::ScriptItemFilterError> *)_Args )
        {
          v925 = v924[2]._Mypair._Myval2._Myfirst;
          Buf = v924[2]._Mypair._Myval2._Mylast->mMessage._Mypair._Myval2._Bx._Buf;
        }
        else
        {
          std::vector<ScriptModuleMinecraft::ScriptItemFilterError>::_Tidy(this: v924 + 2);
          v925 = *(ScriptModuleMinecraft::ScriptItemFilterError **)&_Args[0].mIgnored;
          v924[2]._Mypair._Myval2._Myfirst = *(ScriptModuleMinecraft::ScriptItemFilterError **)&_Args[0].mIgnored;
          Buf = _Args[0].mDefNamespace._Mypair._Myval2._Bx._Ptr;
          *(std::_String_val<std::_Simple_types<char> >::_Bxty *)&v924[2]._Mypair._Myval2._Mylast = _Args[0].mDefNamespace._Mypair._Myval2._Bx;
          memset(_Args, 0, 24);
        }
        v924->_Mypair._Myval2._Myend = (ScriptModuleMinecraft::ScriptItemFilterError *)((Buf - (char *)v925) >> 5);
        std::vector<ScriptModuleMinecraft::ScriptItemFilterError>::_Tidy(this: (std::vector<ScriptModuleMinecraft::ScriptItemFilterError> *)_Args);
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)def);
        goto LABEL_1733;
      }
      *(_QWORD *)&_Args[0].mIgnored = v196;
      v354 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v197[23]._Mypair._Myval2 + (unsigned int)(8 * v201));
      v355 = v197[24]._Mypair._Myval2;
      if ( v355 == v197[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v197 + 23,
          _Val: v354);
        v390 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v355 == (StructureFeature *)v354 )
        {
          v355->__vftable = (StructureFeature_vtbl *)v196;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1715:
          ownerControl->mComponentsInUse |= v198;
          goto LABEL_1716;
        }
        v356 = (std::unique_ptr<RuinedPortalFeature> *)&v355[-1].mActiveBlueprintCreateCount;
        v357 = *(StructureFeature_vtbl **)&v355[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v355[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v355->__vftable = v357;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v356 != v354 )
        {
          v358 = v356[-1]._Mypair._Myval2;
          v359 = v356->_Mypair._Myval2;
          v356[-1]._Mypair._Myval2 = nullptr;
          v356->_Mypair._Myval2 = v358;
          if ( v359 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v359->dtr_StructureFeature)(a1: v359, a2: 1);
          --v356;
        }
        v390 = v354->_Mypair._Myval2;
        v354->_Mypair._Myval2 = (RuinedPortalFeature *)v196;
      }
      if ( v390 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v390->dtr_StructureFeature)(a1: v390, a2: 1);
      goto LABEL_1715;
    case 22LL:
      v240 = (UIControl *)v1110;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v240);
      UIControlFactory::_populateGridComponent(
        context: (const UIControlFactoryContext *)def,
        def: resolvedDef,
        ownerControl: v240);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v240);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v240);
      LOBYTE(v241) = 27;
      LOBYTE(def) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                      this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                      a2: (Memory::MemoryCategory)v241);
      v242 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 136);
      if ( v242 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x88u, alignment: 0);
      v243 = (std::unique_ptr<StructureFeature> *)ownerControl;
      *((_QWORD *)v242 + 1) = ownerControl;
      *(_QWORD *)v242 = &PageIndicatorGridComponent::`vftable';
      *((_OWORD *)v242 + 1) = 0;
      *((_OWORD *)v242 + 2) = 0;
      *((_OWORD *)v242 + 3) = 0;
      *((_OWORD *)v242 + 4) = 0;
      *((_QWORD *)v242 + 10) = 15;
      *(_OWORD *)(v242 + 88) = 0;
      *((_QWORD *)v242 + 13) = 0;
      *((_QWORD *)v242 + 14) = 15;
      *(_OWORD *)(v242 + 120) = 0;
      if ( dword_151E0C9A8 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &dword_151E0C9A8);
        if ( dword_151E0C9A8 == -1 )
        {
          qword_151E0C9A0 = 1LL << _InterlockedExchangeAdd64(
                                     (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                     1u);
          Init_thread_footer(pOnce: &dword_151E0C9A8);
        }
      }
      v244 = qword_151E0C9A0;
      v245 = v243[22]._Mypair._Myval2;
      v246 = (((unsigned __int64)v245 & (qword_151E0C9A0 - 1))
            - ((((unsigned __int64)v245 & (qword_151E0C9A0 - 1)) >> 1) & 0x5555555555555555LL))
           & 0x3333333333333333LL;
      v247 = (0x101010101010101LL
            * ((v246
              + (((((unsigned __int64)v245 & (qword_151E0C9A0 - 1))
                 - ((((unsigned __int64)v245 & (qword_151E0C9A0 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
               & 0x3333333333333333LL)
              + ((v246
                + (((((unsigned __int64)v245 & (qword_151E0C9A0 - 1))
                   - ((((unsigned __int64)v245 & (qword_151E0C9A0 - 1)) >> 1) & 0x5555555555555555LL)) >> 2)
                 & 0x3333333333333333LL)) >> 4))
             & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v248 = v243 + 23;
      if ( (qword_151E0C9A0 & (unsigned __int64)v245) != 0 )
      {
        v249 = *((RenderableComponent **)&v248->_Mypair._Myval2->__vftable + v247);
        v1053 = v242;
        v250 = guard_dispatch_icall_nop(a1: v249);
        v1053 = v242;
        v251 = guard_dispatch_icall_nop(a1: v249);
        if ( (v251 | v250) == 1 )
        {
          if ( v250 != 0 )
          {
            v252 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
            v253 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            if ( v252 != v253 )
            {
              while ( *v252 != v249 )
              {
                if ( ++v252 == v253 )
                  goto LABEL_541;
              }
            }
            if ( v252 != v253 )
            {
              v428 = v251;
              memmove_0(a1: v252, Src: v252 + 1, Size: (char *)v253 - (char *)(v252 + 1));
              v251 = v428;
              --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
            }
          }
LABEL_541:
          if ( v251 != 0 )
          {
            v429 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
            v430 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            if ( v429 != v430 )
            {
              while ( *v429 != (CustomFrameUpdateComponent *)v249 )
              {
                if ( ++v429 == v430 )
                  goto LABEL_548;
              }
            }
            if ( v429 != v430 )
            {
              memmove_0(a1: v429, Src: v429 + 1, Size: (char *)v430 - (char *)(v429 + 1));
              --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
            }
          }
        }
LABEL_548:
        v431 = *((void (__fastcall ****)(_QWORD, __int64))&v248->_Mypair._Myval2->__vftable + v247);
        *((_QWORD *)&v248->_Mypair._Myval2->__vftable + v247) = v242;
        if ( v431 != nullptr )
          (**v431)(a1: v431, a2: 1);
LABEL_1401:
        v1053 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v242) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v242;
          v777 = ownerControl;
          v778 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v778 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
          {
            v1053 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v778);
          }
          else
          {
            *v778 = (RenderableComponent *)v242;
            ++v777->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        v1053 = nullptr;
        if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v242) != 0 )
        {
          *(_QWORD *)&_Args[0].mIgnored = v242;
          v779 = ownerControl;
          v780 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v780 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
          {
            v1053 = nullptr;
            std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
              _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
              _Val: (bgfx::d3d12::BufferHeapBlock *const *)v780);
          }
          else
          {
            *v780 = (CustomFrameUpdateComponent *)v242;
            ++v779->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
        *(_QWORD *)&_Args[0].mIgnored = off_14E8D7570;
        _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
        *(_QWORD *)&defaultValue.mFileSystem = u;
        defaultValue.mPath.mContainer._Mypair._Myval2._Bx._Ptr = nullptr;
        Src._Mypair._Myval2._Bx._Ptr = "cycler_manager_size_control_target";
        *(_QWORD *)&Src._Mypair._Myval2._Bx._Alias[8] = 34;
        v1084 = 1;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&Src,
          (std::string_view *)&defaultValue);
        UIControl::_registerControlNameResolver(
          controlName: (const std::string *)ownerControl,
          scope: (ui::NameResolutionScope)&v1079,
          setter: nullptr);
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v781 = *(void **)&v1079.mIgnored;
          v782 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v782 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v781 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v781, __formal: v782);
        }
        if ( dword_151E0C9A8 > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
        {
          Init_thread_header(pOnce: &dword_151E0C9A8);
          if ( dword_151E0C9A8 == -1 )
          {
            qword_151E0C9A0 = 1LL << _InterlockedExchangeAdd64(
                                       (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                       1u);
            Init_thread_footer(pOnce: &dword_151E0C9A8);
          }
        }
        v783 = ownerControl->mComponentsInUse;
        if ( (qword_151E0C9A0 & v783) != 0
          && (v784 = ((qword_151E0C9A0 - 1) & v783) - ((((qword_151E0C9A0 - 1) & v783) >> 1) & 0x5555555555555555LL),
              v785 = (0x101010101010101LL
                    * (((v784 & 0x3333333333333333LL)
                      + ((v784 >> 2) & 0x3333333333333333LL)
                      + (((v784 & 0x3333333333333333LL) + ((v784 >> 2) & 0x3333333333333333LL)) >> 4))
                     & 0xF0F0F0F0F0F0F0FLL)) >> 56,
              v786 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
              ownerControl->mComponents._Mypair._Myval2._Mylast - v786 > v785) )
        {
          v787 = v786[v785]._Mypair._Myval2;
        }
        else
        {
          v787 = nullptr;
        }
        v1106._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&v1106._Mypair._Myval2._Bx._Alias[8] = 0;
        v1069._Mypair._Myval2._Bx._Ptr = "grid_item_when_current";
        *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 22;
        v788 = &v1079;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&v1069,
          defaultValue: (std::string_view *)&v1106);
        v790 = (UIControl *)&v787[3].mOwner;
        if ( &v787[3].mOwner != (UIControl **)&v1079 )
        {
          v791 = *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
            v788 = *(UIResolvedDef **)&v1079.mIgnored;
          v792 = (unsigned __int64)v787[5].__vftable;
          if ( *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v792 )
          {
            if ( v792 >= 0x10 )
              v790 = v787[3].mOwner;
            v787[4].mOwner = *(UIControl **)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
            memmove_0(a1: v790, Src: v788, Size: v791);
            *((_BYTE *)&v790->_Wptr._Ptr + v791) = 0;
          }
          else
          {
            ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
              this: (std::string *)&v787[3].mOwner,
              _New_size: *(const unsigned __int64 *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8],
              _Fn: v789,
              _Args: (const char *)&v788->mIgnored);
          }
        }
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v793 = *(void **)&v1079.mIgnored;
          v794 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v794 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v793 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v793, __formal: v794);
        }
        __formal._Mypair._Myval2._Bx._Ptr = (char *)u;
        *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 0;
        v1076._Mypair._Myval2._Bx._Ptr = "grid_item_when_not_current";
        *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 26;
        v795 = &v1079;
        UIResolvedDef::getAsString(
          this: v1110,
          result: (std::string *)&v1079,
          key: (std::string_view *)&v1076,
          defaultValue: (std::string_view *)&__formal);
        v797 = (UIControl *)&v787[5].mOwner;
        if ( &v787[5].mOwner != (UIControl **)&v1079 )
        {
          v798 = *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
            v795 = *(UIResolvedDef **)&v1079.mIgnored;
          v799 = (unsigned __int64)v787[7].__vftable;
          if ( *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v799 )
          {
            if ( v799 >= 0x10 )
              v797 = v787[5].mOwner;
            v787[6].mOwner = *(UIControl **)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8];
            memmove_0(a1: v797, Src: v795, Size: v798);
            *((_BYTE *)&v797->_Wptr._Ptr + v798) = 0;
          }
          else
          {
            ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
              this: (std::string *)&v787[5].mOwner,
              _New_size: *(const unsigned __int64 *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8],
              _Fn: v796,
              _Args: (const char *)&v795->mIgnored);
          }
        }
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
        {
          v800 = *(void **)&v1079.mIgnored;
          v801 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
          if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
          {
            if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
              goto LABEL_1922;
            v801 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
            v800 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
          }
          operator delete(block: v800, __formal: v801);
        }
        Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
          this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
          a2: (Memory::MemoryCategory)def);
        goto LABEL_1733;
      }
      *(_QWORD *)&_Args[0].mIgnored = v242;
      v330 = (std::unique_ptr<RuinedPortalFeature> *)((char *)v243[23]._Mypair._Myval2 + (unsigned int)(8 * v247));
      v331 = v243[24]._Mypair._Myval2;
      if ( v331 == v243[25]._Mypair._Myval2 )
      {
        std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
          _Whereptr: v243 + 23,
          _Val: v330);
        v386 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
      }
      else
      {
        if ( v331 == (StructureFeature *)v330 )
        {
          v331->__vftable = (StructureFeature_vtbl *)v242;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1400:
          ownerControl->mComponentsInUse |= v244;
          goto LABEL_1401;
        }
        v332 = (std::unique_ptr<RuinedPortalFeature> *)&v331[-1].mActiveBlueprintCreateCount;
        v333 = *(StructureFeature_vtbl **)&v331[-1].mActiveBlueprintCreateCount._Storage._Value;
        *(_QWORD *)&v331[-1].mActiveBlueprintCreateCount._Storage._Value = 0;
        v331->__vftable = v333;
        ++ownerControl->mComponents._Mypair._Myval2._Mylast;
        while ( v332 != v330 )
        {
          v334 = v332[-1]._Mypair._Myval2;
          v335 = v332->_Mypair._Myval2;
          v332[-1]._Mypair._Myval2 = nullptr;
          v332->_Mypair._Myval2 = v334;
          if ( v335 != nullptr )
            ((void (__fastcall *)(RuinedPortalFeature *, __int64))v335->dtr_StructureFeature)(a1: v335, a2: 1);
          --v332;
        }
        v386 = v330->_Mypair._Myval2;
        v330->_Mypair._Myval2 = (RuinedPortalFeature *)v242;
      }
      if ( v386 != nullptr )
        ((void (__fastcall *)(RuinedPortalFeature *, __int64))v386->dtr_StructureFeature)(a1: v386, a2: 1);
      goto LABEL_1400;
    case 23LL:
      v255 = (UIControl *)v1110;
      v256 = ownerControl;
      UIControlFactory::_populateControl(def, control: (UIControl *)v1110);
      UIControlFactory::_populateDataBindingComponent(def, ownerControl: v255);
      UIControlFactory::_populateFocusComponent(def, ownerControl: v255);
      UIControlFactory::_populateInputComponent(def, ownerControl: v255);
      UIControlFactory::_populateLayoutComponent(def, ownerControl: v255);
      UIControlFactory::_populateGestureComponent(def: (const UIResolvedDef *)v255, ownerControl: v256);
      UIControlFactory::_populateSoundComponent(def, ownerControl: v255, a3: (bool)v256);
      LOBYTE(v257) = 27;
      LOBYTE(v1108) = Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
                        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
                        a2: (Memory::MemoryCategory)v257);
      v258 = (char *)Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value->_allocate(
                       this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryAllocator._Storage._Value,
                       a2: 104);
      if ( v258 == nullptr )
        `anonymous namespace'::MemoryAnon::reportBadAlloc(size: 0x68u, alignment: 0);
      *((_QWORD *)v258 + 1) = ownerControl;
      *(_QWORD *)v258 = &off_14E8D6770;
      v258[16] = 0;
      *(_OWORD *)(v258 + 20) = 0;
      *(_OWORD *)(v258 + 36) = 0;
      *(_OWORD *)(v258 + 52) = 0;
      *(_OWORD *)(v258 + 68) = 0;
      *((_OWORD *)v258 + 5) = 0;
      *((_QWORD *)v258 + 12) = 15;
      def = (UIResolvedDef *)v258;
      TooltipTriggerComponent::_updateControlVisibility(a1: v258);
      if ( __TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                               (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                               1u);
          `uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v259 = `uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId;
      v260 = ownerControl->mComponentsInUse;
      v261 = (((v260 & (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1))
             - (((v260 & (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1)) >> 1)
              & 0x5555555555555555LL))
            & 0x3333333333333333LL)
           + ((((v260 & (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1))
              - (((v260 & (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1)) >> 1)
               & 0x5555555555555555LL)) >> 2)
            & 0x3333333333333333LL);
      v262 = (0x101010101010101LL * ((v261 + (v261 >> 4)) & 0xF0F0F0F0F0F0F0FLL)) >> 56;
      v263 = &ownerControl->mComponents;
      v264 = def;
      if ( (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId & v260) == 0 )
      {
        *(_QWORD *)&_Args[0].mIgnored = def;
        v360 = (std::unique_ptr<RuinedPortalFeature> *)((char *)ownerControl->mComponents._Mypair._Myval2._Myfirst
                                                      + (unsigned int)(8 * v262));
        v361 = ownerControl->mComponents._Mypair._Myval2._Mylast;
        if ( v361 == ownerControl->mComponents._Mypair._Myval2._Myend )
        {
          std::vector_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature____std::allocator_std::unique_ptr_StructureFeature_std::default_delete_StructureFeature_______::_Emplace_reallocate_std::unique_ptr_RuinedPortalFeature_std::default_delete_RuinedPortalFeature_____(
            _Whereptr: (std::unique_ptr<StructureFeature> *)&ownerControl->mComponents,
            _Val: v360);
          v391 = *(RuinedPortalFeature **)&_Args[0].mIgnored;
        }
        else
        {
          if ( v361 == (std::unique_ptr<UIComponent> *)v360 )
          {
            v361->_Mypair._Myval2 = (UIComponent *)def;
            ++ownerControl->mComponents._Mypair._Myval2._Mylast;
LABEL_1737:
            ownerControl->mComponentsInUse |= v259;
            goto LABEL_1738;
          }
          v362 = (std::unique_ptr<RuinedPortalFeature> *)&v361[-1];
          v363 = v361[-1]._Mypair._Myval2;
          v361[-1]._Mypair._Myval2 = nullptr;
          v361->_Mypair._Myval2 = v363;
          ++ownerControl->mComponents._Mypair._Myval2._Mylast;
          while ( v362 != v360 )
          {
            v364 = v362[-1]._Mypair._Myval2;
            v365 = v362->_Mypair._Myval2;
            v362[-1]._Mypair._Myval2 = nullptr;
            v362->_Mypair._Myval2 = v364;
            if ( v365 != nullptr )
              ((void (__fastcall *)(RuinedPortalFeature *, __int64))v365->dtr_StructureFeature)(a1: v365, a2: 1);
            --v362;
          }
          v391 = v360->_Mypair._Myval2;
          v360->_Mypair._Myval2 = (RuinedPortalFeature *)v264;
        }
        if ( v391 != nullptr )
          ((void (__fastcall *)(RuinedPortalFeature *, __int64))v391->dtr_StructureFeature)(a1: v391, a2: 1);
        goto LABEL_1737;
      }
      v265 = (RenderableComponent *)v263->_Mypair._Myval2._Myfirst[v262]._Mypair._Myval2;
      v1052 = def;
      v266 = guard_dispatch_icall_nop(a1: v265);
      v1052 = def;
      v267 = guard_dispatch_icall_nop(a1: v265);
      if ( (v267 | v266) == 1 )
      {
        if ( v266 != 0 )
        {
          v268 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myfirst;
          v269 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          if ( v268 != v269 )
          {
            while ( *v268 != v265 )
            {
              if ( ++v268 == v269 )
                goto LABEL_596;
            }
          }
          if ( v268 != v269 )
          {
            v448 = v267;
            memmove_0(a1: v268, Src: v268 + 1, Size: (char *)v269 - (char *)(v268 + 1));
            v267 = v448;
            --ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
          }
        }
LABEL_596:
        if ( v267 != 0 )
        {
          v449 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myfirst;
          v450 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          if ( v449 != v450 )
          {
            while ( *v449 != (CustomFrameUpdateComponent *)v265 )
            {
              if ( ++v449 == v450 )
                goto LABEL_603;
            }
          }
          if ( v449 != v450 )
          {
            memmove_0(a1: v449, Src: v449 + 1, Size: (char *)v450 - (char *)(v449 + 1));
            --ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
          }
        }
      }
LABEL_603:
      v451 = v263->_Mypair._Myval2._Myfirst[v262]._Mypair._Myval2;
      v264 = def;
      v263->_Mypair._Myval2._Myfirst[v262]._Mypair._Myval2 = (UIComponent *)def;
      if ( v451 != nullptr )
        ((void (__fastcall *)(UIComponent *, __int64))v451->dtr_UIComponent)(a1: v451, a2: 1);
LABEL_1738:
      v1052 = nullptr;
      if ( (unsigned __int8)guard_dispatch_icall_nop(a1: v264) != 0 )
      {
        *(_QWORD *)&_Args[0].mIgnored = def;
        v928 = ownerControl;
        v929 = ownerControl->mRenderableComponentLookup._Mypair._Myval2._Mylast;
        if ( v929 == ownerControl->mRenderableComponentLookup._Mypair._Myval2._Myend )
        {
          v1052 = nullptr;
          std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
            _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mRenderableComponentLookup,
            _Val: (bgfx::d3d12::BufferHeapBlock *const *)v929);
        }
        else
        {
          *v929 = (RenderableComponent *)def;
          ++v928->mRenderableComponentLookup._Mypair._Myval2._Mylast;
        }
      }
      v1052 = nullptr;
      if ( (unsigned __int8)guard_dispatch_icall_nop(a1: def) != 0 )
      {
        *(_QWORD *)&_Args[0].mIgnored = def;
        v930 = ownerControl;
        v931 = ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
        if ( v931 == ownerControl->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Myend )
        {
          v1052 = nullptr;
          std::vector_bgfx::d3d12::BufferHeapBlock___std::allocator_bgfx::d3d12::BufferHeapBlock_____::_Emplace_reallocate_bgfx::d3d12::BufferHeapBlock__const___(
            _Whereptr: (bgfx::d3d12::BufferHeapBlock **)&ownerControl->mCustomFrameUpdateComponentLookup,
            _Val: (bgfx::d3d12::BufferHeapBlock *const *)v931);
        }
        else
        {
          *v931 = (CustomFrameUpdateComponent *)def;
          ++v930->mCustomFrameUpdateComponentLookup._Mypair._Myval2._Mylast;
        }
      }
      if ( __TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA > *(_DWORD *)(*((_QWORD *)NtCurrentTeb()->Reserved1[11] + tls_index) + 4LL) )
      {
        Init_thread_header(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        if ( __TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA == -1 )
        {
          `uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mID = _InterlockedExchangeAdd64(
                                                                               (volatile signed __int64 *)&uicontrolid_t<UIComponent>::mCount,
                                                                               1u);
          `uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId = 1LL << SLOBYTE(`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mID);
          Init_thread_footer(pOnce: &__TSS0__1____uicontrol_id_VUIComponent__VTooltipTriggerComponent____YAAEBV__uicontrolid_t_VUIComponent____XZ_4HA);
        }
      }
      v932 = ownerControl->mComponentsInUse;
      if ( (`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId & v932) != 0
        && (v933 = ((`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1) & v932)
                 - ((((`uicontrol_id<UIComponent,TooltipTriggerComponent>'::`2'::id.mBitId - 1) & v932) >> 1)
                  & 0x5555555555555555LL),
            v934 = (0x101010101010101LL
                  * (((v933 & 0x3333333333333333LL)
                    + ((v933 >> 2) & 0x3333333333333333LL)
                    + (((v933 & 0x3333333333333333LL) + ((v933 >> 2) & 0x3333333333333333LL)) >> 4))
                   & 0xF0F0F0F0F0F0F0FLL)) >> 56,
            v935 = ownerControl->mComponents._Mypair._Myval2._Myfirst,
            ownerControl->mComponents._Mypair._Myval2._Mylast - v935 > v934) )
      {
        v936 = v935[v934]._Mypair._Myval2;
      }
      else
      {
        v936 = nullptr;
      }
      v1069._Mypair._Myval2._Bx._Ptr = (char *)u;
      *(_QWORD *)&v1069._Mypair._Myval2._Bx._Alias[8] = 0;
      __formal._Mypair._Myval2._Bx._Ptr = "tooltip_name";
      *(_QWORD *)&__formal._Mypair._Myval2._Bx._Alias[8] = 12;
      v937 = &Src;
      UIResolvedDef::getAsString(
        this: v1110,
        result: &Src,
        key: (std::string_view *)&__formal,
        defaultValue: (std::string_view *)&v1069);
      if ( Src._Mypair._Myval2._Myres >= 0x10 )
        v937 = (std::string *)Src._Mypair._Myval2._Bx._Ptr;
      if ( Src._Mypair._Myval2._Mysize != 0 )
      {
        if ( Src._Mypair._Myval2._Mysize >= 8 )
        {
          v939 = Src._Mypair._Myval2._Mysize & 0xFFFFFFFFFFFFFFF8uLL;
          v938 = -2128831035;
          do
          {
            v938 = 16777619
                 * ((16777619
                   * ((16777619
                     * ((16777619
                       * ((16777619
                         * ((16777619
                           * ((16777619
                             * ((16777619 * (v938 ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[0]))
                              ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[1]))
                            ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[2]))
                          ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[3]))
                        ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[4]))
                      ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[5]))
                    ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[6]))
                  ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[7]);
            v937 = (std::string *)((char *)v937 + 8);
            v939 -= 8LL;
          }
          while ( v939 != 0 );
        }
        else
        {
          v938 = -2128831035;
        }
        if ( (Src._Mypair._Myval2._Mysize & 7) != 0 )
        {
          v940 = 0;
          do
            v938 = 16777619 * (v938 ^ (unsigned __int8)v937->_Mypair._Myval2._Bx._Buf[v940++]);
          while ( (Src._Mypair._Myval2._Mysize & 7) != v940 );
        }
      }
      else
      {
        v938 = -2128831035;
      }
      HIDWORD(v936[1].__vftable) = v938;
      v1076._Mypair._Myval2._Bx._Ptr = (char *)&Util::EMPTY_STRING;
      *(_QWORD *)&v1076._Mypair._Myval2._Bx._Alias[8] = 0;
      v1073._Mypair._Myval2._Bx._Ptr = "tooltip_tts_value";
      *(_QWORD *)&v1073._Mypair._Myval2._Bx._Alias[8] = 17;
      v941 = _Args;
      UIResolvedDef::getAsString(
        this: v1110,
        result: (std::string *)_Args,
        key: (std::string_view *)&v1073,
        defaultValue: (std::string_view *)&v1076);
      v943 = (UIControl *)&v936[4].mOwner;
      if ( &v936[4].mOwner != (UIControl **)_Args )
      {
        v944 = *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v941 = *(UIResolvedDef **)&_Args[0].mIgnored;
        v945 = (unsigned __int64)v936[6].__vftable;
        if ( *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] <= v945 )
        {
          if ( v945 >= 0x10 )
            v943 = v936[4].mOwner;
          v936[5].mOwner = *(UIControl **)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8];
          memmove_0(a1: v943, Src: v941, Size: v944);
          *((_BYTE *)&v943->_Wptr._Ptr + v944) = 0;
        }
        else
        {
          ____Reallocate_for_V_lambda_1___0__assign___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__QEAAAEAV34_QEBD_K_Z_PEBD___basic_string_DU__char_traits_D_std__V__allocator_D_2__std__AEAAAEAV01__KV_lambda_1___0__assign_01_QEAAAEAV01_QEBD0_Z_PEBD_Z(
            this: (std::string *)&v936[4].mOwner,
            _New_size: *(const unsigned __int64 *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8],
            _Fn: v942,
            _Args: (const char *)&v941->mIgnored);
        }
      }
      if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
      {
        v946 = *(void **)&_Args[0].mIgnored;
        v947 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v947 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
          v946 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
        }
        operator delete(block: v946, __formal: v947);
      }
      *(_QWORD *)&_Args[0].mIgnored = off_14E8D75A0;
      _Args[0].mDefName._Mypair._Myval2._Mysize = (unsigned __int64)_Args;
      v1072._Mypair._Myval2._Bx = (std::_String_val<std::_Simple_types<char> >::_Bxty)(unsigned __int64)u;
      v1068._Mypair._Myval2._Bx._Ptr = "tooltip_top_content_control";
      *(_QWORD *)&v1068._Mypair._Myval2._Bx._Alias[8] = 27;
      v1083 = 1;
      UIResolvedDef::getAsString(
        this: v1110,
        result: (std::string *)&v1079,
        key: (std::string_view *)&v1068,
        defaultValue: (std::string_view *)&v1072);
      UIControl::_registerControlNameResolver(
        controlName: (const std::string *)ownerControl,
        scope: (ui::NameResolutionScope)&v1079,
        setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)2);
      if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
      {
        v948 = *(void **)&v1079.mIgnored;
        v949 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v949 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
          v948 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
        }
        operator delete(block: v948, __formal: v949);
      }
      *(_QWORD *)&v1079.mIgnored = off_14E8D75D0;
      v1079.mDefName._Mypair._Myval2._Mysize = (unsigned __int64)&v1079;
      v1048._Mypair._Myval2._Bx._Ptr = (char *)u;
      *(_QWORD *)&v1048._Mypair._Myval2._Bx._Alias[8] = 0;
      v1049._Mypair._Myval2._Bx._Ptr = "tooltip_bottom_content_control";
      *(_QWORD *)&v1049._Mypair._Myval2._Bx._Alias[8] = 30;
      v1082 = 1;
      UIResolvedDef::getAsString(
        this: v1110,
        result: (std::string *)&defaultValue,
        key: (std::string_view *)&v1049,
        defaultValue: (std::string_view *)&v1048);
      UIControl::_registerControlNameResolver(
        controlName: (const std::string *)ownerControl,
        scope: (ui::NameResolutionScope)&defaultValue,
        setter: (std::function<void (UIControl &, std::shared_ptr<UIControl>)> *)2);
      if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
      {
        v950 = *(void **)&defaultValue.mFileSystem;
        v951 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                - 8LL
                                - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v951 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
          v950 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
        }
        operator delete(block: v950, __formal: v951);
      }
      *(_QWORD *)&defaultValue.mFileSystem = off_14E8D7600;
      v1078 = &defaultValue;
      v1046._Mypair._Myval2._Bx._Ptr = (char *)u;
      *(_QWORD *)&v1046._Mypair._Myval2._Bx._Alias[8] = 0;
      v1071._Mydata = "tooltip_area";
      v1071._Mysize = 12;
      v1081 = 1;
      UIResolvedDef::getAsString(this: v1110, result: &v1106, key: &v1071, defaultValue: (std::string_view *)&v1046);
      UIControl::_registerControlNameResolver(
        controlName: (const std::string *)ownerControl,
        scope: (ui::NameResolutionScope)&v1106,
        setter: nullptr);
      if ( v1106._Mypair._Myval2._Myres >= 0x10 )
      {
        v952 = v1106._Mypair._Myval2._Bx._Ptr;
        v953 = v1106._Mypair._Myval2._Myres + 1;
        if ( v1106._Mypair._Myval2._Myres + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)&v1106._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)v1106._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
            goto LABEL_1922;
          v953 = v1106._Mypair._Myval2._Myres + 40;
          v952 = *((char **)v1106._Mypair._Myval2._Bx._Ptr - 1);
        }
        operator delete(block: v952, __formal: v953);
      }
      if ( Src._Mypair._Myval2._Myres >= 0x10 )
      {
        v954 = Src._Mypair._Myval2._Bx._Ptr;
        v955 = Src._Mypair._Myval2._Myres + 1;
        if ( Src._Mypair._Myval2._Myres + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)&Src._Mypair._Myval2._Bx._Ptr[-*((_QWORD *)Src._Mypair._Myval2._Bx._Ptr - 1) - 8] >= 0x20 )
            goto LABEL_1922;
          v955 = Src._Mypair._Myval2._Myres + 40;
          v954 = *((char **)Src._Mypair._Myval2._Bx._Ptr - 1);
        }
        operator delete(block: v954, __formal: v955);
      }
      Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value->exchangeCurrentCategory(
        this: Memory::`anonymous namespace'::MemoryTrackerAnon::memoryTracker._Storage._Value,
        a2: (Memory::MemoryCategory)v1108);
      v43 = ownerControl;
      UIControlFactory::_populateTextToSpeechComponent(def: v1110, ownerControl, controlPriorityDefault: 1000);
LABEL_1734:
      v272 = p_Pmtx;
      *p_Pmtx = v43;
      v272[1] = v1047[1];
      ContentLog::ContentLogScope::~ContentLogScope(this: &v1008);
      return (std::shared_ptr<UIControl> *)v272;
    default:
      memset(_Args, 0, 32);
      v270 = v1110->mDefName._Mypair._Myval2._Mysize;
      if ( v1110->mDefName._Mypair._Myval2._Myres < 0x10 )
        v271 = &v1110->mDefName;
      else
        v271 = (const std::string *)v1110->mDefName._Mypair._Myval2._Bx._Ptr;
      v272 = p_Pmtx;
      if ( v270 < 0 )
        std::_Xlen_string();
      if ( (unsigned __int64)v270 > 0xF )
      {
        v273 = 22;
        if ( (v270 | 0xFuLL) >= 0x17 )
          v273 = v270 | 0xF;
        if ( (v270 | 0xFuLL) < 0xFFF )
        {
          v275 = operator new(size: v273 + 1);
        }
        else
        {
          v274 = operator new(size: v273 + 40);
          v275 = (_QWORD *)(((unsigned __int64)v274 + 39) & 0xFFFFFFFFFFFFFFE0uLL);
          *(v275 - 1) = v274;
        }
        *(_QWORD *)&_Args[0].mIgnored = v275;
        *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] = v270;
        _Args[0].mDefNamespace._Mypair._Myval2._Mysize = v273;
        memcpy_0(a1: v275, Src: v271, Size: v270 + 1);
        v272 = p_Pmtx;
      }
      else
      {
        *(_QWORD *)&_Args[0].mDefNamespace._Mypair._Myval2._Bx._Alias[8] = v1110->mDefName._Mypair._Myval2._Mysize;
        _Args[0].mDefNamespace._Mypair._Myval2._Mysize = 15;
        *(__m128i *)&_Args[0].mIgnored = _mm_loadu_si128((const __m128i *)v271);
      }
      v1030._Mydata = "type";
      v1030._Mysize = 4;
      v366 = UIResolvedDef::getValue(this: v1110, key: &v1030, a3: false);
      memset(&defaultValue, 0, 24);
      defaultValue.mPath.mContainer._Mypair._Myval2._Mysize = 15;
      v367 = &v1079;
      Json::Value::asString(this: v366, result: (std::string *)&v1079, (const std::string *)&defaultValue);
      if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize >= 0x10 )
      {
        v368 = *(void **)&defaultValue.mFileSystem;
        v369 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1;
        if ( defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&defaultValue.mFileSystem
                                - 8LL
                                - *(_QWORD *)(*(_QWORD *)&defaultValue.mFileSystem - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v369 = defaultValue.mPath.mContainer._Mypair._Myval2._Mysize + 40;
          v368 = *(void **)(*(_QWORD *)&defaultValue.mFileSystem - 8LL);
        }
        operator delete(block: v368, __formal: v369);
      }
      if ( *(_QWORD *)&v1079.mDefNamespace._Mypair._Myval2._Bx._Alias[8] != 0 )
      {
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
          v367 = *(UIResolvedDef **)&v1079.mIgnored;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize < 0x10 )
          v370 = _Args;
        else
          v370 = *(UIResolvedDef **)&_Args[0].mIgnored;
        *(_QWORD *)&defaultValue.mFileSystem = v370;
        Src._Mypair._Myval2._Bx._Ptr = (char *)&v367->mIgnored;
        ContentLogHelper::_contentLog<char const (&)[207],char const *,unsigned __int64 const &>(
          level: true,
          area: (const LogLevel)3,
          args: UI,
          a4: (const char (*)[74])"Type '%s' not recognized for control: %s",
          a5: (const char **)&Src,
          a6: (const char **)&defaultValue);
      }
      else
      {
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize < 0x10 )
          v371 = _Args;
        else
          v371 = *(UIResolvedDef **)&_Args[0].mIgnored;
        *(_QWORD *)&defaultValue.mFileSystem = v371;
        ContentLogHelper::_contentLog<char const (&)[45],char const * &>(
          level: true,
          area: (const LogLevel)3,
          args: UI,
          a4: (const char (*)[15])"Type not specified (or @-base not found) for control: %s",
          a5: (const char **)&defaultValue);
      }
      *(_OWORD *)v272 = 0;
      if ( v1079.mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
      {
        v372 = *(void **)&v1079.mIgnored;
        v373 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 1;
        if ( v1079.mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&v1079.mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&v1079.mIgnored - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v373 = v1079.mDefNamespace._Mypair._Myval2._Mysize + 40;
          v372 = *(void **)(*(_QWORD *)&v1079.mIgnored - 8LL);
        }
        operator delete(block: v372, __formal: v373);
      }
      if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize >= 0x10 )
      {
        v374 = *(void **)&_Args[0].mIgnored;
        v375 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1;
        if ( _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 1 >= 0x1000 )
        {
          if ( (unsigned __int64)(*(_QWORD *)&_Args[0].mIgnored - 8LL - *(_QWORD *)(*(_QWORD *)&_Args[0].mIgnored - 8LL)) >= 0x20 )
            goto LABEL_1922;
          v375 = _Args[0].mDefNamespace._Mypair._Myval2._Mysize + 40;
          v374 = *(void **)(*(_QWORD *)&_Args[0].mIgnored - 8LL);
        }
        operator delete(block: v374, __formal: v375);
      }
      v376 = (volatile signed __int32 *)v1047[1];
      ContentLog::ContentLogScope::~ContentLogScope(this: &v1008);
      if ( v376 != nullptr && _InterlockedDecrement(v376 + 2) == 0 )
      {
        (**(void (__fastcall ***)(volatile signed __int32 *))v376)(a1: v376);
        if ( _InterlockedDecrement(v376 + 3) == 0 )
          (*(void (__fastcall **)(volatile signed __int32 *))(*(_QWORD *)v376 + 8LL))(a1: v376);
      }
      return (std::shared_ptr<UIControl> *)v272;
  }
}