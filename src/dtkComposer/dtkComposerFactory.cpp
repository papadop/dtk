// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#include "dtkComposerFactory.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeMetaContainer.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeSpawn.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringOperator.h"

#include "dtkComposerNodeLogger.h"
#include "dtkComposerNodePrint.h"

dtkComposerFactory::dtkComposerFactory(void) : dtkComposerNodeFactory()
{
    this->initNodeBoolean();
    this->initNodeControl();
    this->initNodeNumber();
    this->initNodeString();
    this->initNodeContainer();

    this->record(":dtkComposer/dtkComposerNodeComposite.json", dtkComposerNodeCreator<dtkComposerNodeComposite>);
    this->record(":dtkComposer/dtkComposerNodeRemote.json",   dtkComposerNodeCreator<dtkComposerNodeRemote>);
    this->record(":dtkComposer/dtkComposerNodeRemoteSubmit.json",   dtkComposerNodeCreator<dtkComposerNodeRemoteSubmit>);
    this->record(":dtkComposer/dtkComposerNodeSpawn.json",   dtkComposerNodeCreator<dtkComposerNodeSpawn>);
    this->record(":dtkComposer/dtkComposerNodeLogger.json",    dtkComposerNodeCreator<dtkComposerNodeLogger>);
    this->record(":dtkComposer/dtkComposerNodePrint.json",     dtkComposerNodeCreator<dtkComposerNodePrint>);
}

dtkComposerFactory::~dtkComposerFactory(void)
{

}

void dtkComposerFactory::initNodeBoolean(void)
{
    this->record(":dtkComposer/dtkComposerNodeBoolean.json", dtkComposerNodeCreator<dtkComposerNodeBoolean>);

    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorUnaryNot.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorUnaryNot>);

    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryAnd.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryAnd>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryOr.json",   dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryOr>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXor>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNand.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNand>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNor>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXnor.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXnor>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryImp.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryImp>);
    this->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNimp.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNimp>);
}

void dtkComposerFactory::initNodeControl(void)
{
    this->record(":dtkComposer/dtkComposerNodeControlCase.json", dtkComposerNodeCreator<dtkComposerNodeControlCase>);
    this->record(":dtkComposer/dtkComposerNodeControlIf.json",   dtkComposerNodeCreator<dtkComposerNodeControlIf>);

    this->record(":dtkComposer/dtkComposerNodeControlDoWhile.json", dtkComposerNodeCreator<dtkComposerNodeControlDoWhile>);
    this->record(":dtkComposer/dtkComposerNodeControlFor.json",     dtkComposerNodeCreator<dtkComposerNodeControlFor>);
    this->record(":dtkComposer/dtkComposerNodeControlForEach.json", dtkComposerNodeCreator<dtkComposerNodeControlForEach>);
    this->record(":dtkComposer/dtkComposerNodeControlMap.json",     dtkComposerNodeCreator<dtkComposerNodeControlMap>);
    this->record(":dtkComposer/dtkComposerNodeControlWhile.json",   dtkComposerNodeCreator<dtkComposerNodeControlWhile>);
}

void dtkComposerFactory::initNodeNumber(void)
{
    this->record(":dtkComposer/dtkComposerNodeInteger.json", dtkComposerNodeCreator<dtkComposerNodeInteger>);
    this->record(":dtkComposer/dtkComposerNodeReal.json", dtkComposerNodeCreator<dtkComposerNodeReal>);

    // -- Unary operators

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAbs.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAbs>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySqrt.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySqrt>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySquare.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySquare>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryInv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryInv>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryIncr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryIncr>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDecr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDecr>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryFloor.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryFloor>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCeil.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCeil>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRound.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRound>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCos.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCos>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySin.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySin>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryTan.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryTan>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAcos.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAcos>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAsin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAsin>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAtan.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAtan>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDeg2Rad.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDeg2Rad>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRad2Deg.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRad2Deg>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLn.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLn>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLog10.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLog10>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryExp.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryExp>);

    // -- Binary operators

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryEucldiv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryEucldiv>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryModulo.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryModulo>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMin>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMax.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMax>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPlus.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPlus>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMinus.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMinus>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMult.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMult>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryRatio.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryRatio>);

    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPower.json",      dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPower>);
    this->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryNthroot.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryNthroot>);

    // -- Comparator operator

    this->record(":dtkComposer/dtkComposerNodeNumberComparatorEqual.json",    dtkComposerNodeCreator<dtkComposerNodeNumberComparatorEqual>);
    this->record(":dtkComposer/dtkComposerNodeNumberComparatorNotequal.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorNotequal>);

    this->record(":dtkComposer/dtkComposerNodeNumberComparatorGt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGt>);
    this->record(":dtkComposer/dtkComposerNodeNumberComparatorLt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLt>);
    this->record(":dtkComposer/dtkComposerNodeNumberComparatorGte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGte>);
    this->record(":dtkComposer/dtkComposerNodeNumberComparatorLte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLte>);

    this->record(":dtkComposer/dtkComposerNodeNumberAlmosteq.json",    dtkComposerNodeCreator<dtkComposerNodeNumberAlmosteq>);
    this->record(":dtkComposer/dtkComposerNodeNumberNotalmosteq.json", dtkComposerNodeCreator<dtkComposerNodeNumberNotalmosteq>);
}

void dtkComposerFactory::initNodeString(void)
{
    this->record(":dtkComposer/dtkComposerNodeString.json", dtkComposerNodeCreator<dtkComposerNodeString>);
    this->record(":dtkComposer/dtkComposerNodeStringReplace.json", dtkComposerNodeCreator<dtkComposerNodeStringReplace>);
    this->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryAppend.json",   dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryAppend>);
    this->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryLogicEquality.json", dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryLogicEquality>);
}

void dtkComposerFactory::initNodeContainer(void)
{
    this->record(":dtkComposer/dtkComposerNodeMetaContainer.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainer>);
}


// 
// dtkComposerFactory.cpp ends here
