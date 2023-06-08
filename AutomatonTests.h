#pragma once
class AutomatonTests {
public:
	static bool runAutomatonTests();

	static bool runAutomatonOperationsTests();
	static bool runAutomatonUnionTests();
	static bool runAutomatonConcatenationTests();
	static bool runAutomatonKleeneStarTests();
	static bool runAutomatonComplementTests();
	static bool runAutomatonIntersectionTests();
	static bool runAutomatonDifferenceTests();

	static bool runAutomatonFunctionsTests();
	static bool runAutomatonTotalizationTests();
	static bool runAutomatonDeterminizationTests();
	static bool runAutomatonMinimizationTests();
	static bool runAutomatonReverseTests();
	static bool isEmptyLanguageTests();
	static bool runAutomatonGetRegExTests();


};