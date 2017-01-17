#include "stdafx.h"
#include "../CMyArray/CMyIterator.h"

using namespace std;

struct iteratorFixture
{
	int numbers[10];
	CMyIterator<int, false> iter;
	CMyIterator<int, true> rIter;
	iteratorFixture()
		:numbers(),
		iter(CMyIterator<int, false>(&numbers[0])),
		rIter(CMyIterator<int, true>(&numbers[9]))
	{
		for (int i = 0; i <= 9; ++i)
			numbers[i] = i;
	}
};
BOOST_FIXTURE_TEST_SUITE(CMyIterator_, iteratorFixture)
	BOOST_AUTO_TEST_CASE(can_be_dereferenced)
	{
		BOOST_CHECK_EQUAL(*iter, numbers[0]);
		BOOST_CHECK_EQUAL(*rIter, numbers[9]);
	}
	BOOST_AUTO_TEST_CASE(can_be_dereferenced_for_get_access_to_struct_members)
	{
		struct easyStruct
		{
			string data;
		};
		easyStruct example;
		example.data = "data";
		CMyIterator<easyStruct, false> structIter(&example);
		BOOST_CHECK_EQUAL(structIter->data, example.data);
	}
	BOOST_AUTO_TEST_CASE(can_be_incremented)
	{
		++iter;
		++rIter;
		BOOST_CHECK_EQUAL(*iter, numbers[1]);
		BOOST_CHECK_EQUAL(*rIter, numbers[8]);
	}
	BOOST_AUTO_TEST_CASE(can_be_decremented)
	{
		++iter;
		++iter;
		--iter;

		++rIter;
		++rIter;
		--rIter;

		BOOST_CHECK_EQUAL(*iter, numbers[1]);
		BOOST_CHECK_EQUAL(*rIter, numbers[8]);
	}
	BOOST_AUTO_TEST_CASE(can_be_incremented_in_postfix_form)
	{
		BOOST_CHECK_EQUAL(*(iter++), numbers[0]);
		BOOST_CHECK_EQUAL(*iter, numbers[1]);

		BOOST_CHECK_EQUAL(*(rIter++), numbers[9]);
		BOOST_CHECK_EQUAL(*rIter, numbers[8]);
	}
	BOOST_AUTO_TEST_CASE(can_be_decremented_in_postfix_form)
	{
		++iter;
		++iter;
		BOOST_CHECK_EQUAL(*(iter--), numbers[2]);
		BOOST_CHECK_EQUAL(*iter, numbers[1]);

		++rIter;
		++rIter;
		BOOST_CHECK_EQUAL(*(rIter--), numbers[7]);
		BOOST_CHECK_EQUAL(*rIter, numbers[8]);
	}
	BOOST_AUTO_TEST_CASE(can_be_checked_for_equality_with_another)
	{
		auto iterCopy(iter);
		BOOST_CHECK(iterCopy == iter);
		++iter;
		BOOST_CHECK(!(iterCopy == iter));

		auto rIterCopy(rIter);
		BOOST_CHECK(rIterCopy == rIter);
		++rIter;
		BOOST_CHECK(!(rIterCopy == rIter));
	}
	BOOST_AUTO_TEST_CASE(can_be_checked_for_inequality_with_another)
	{
		auto iterCopy(iter);
		BOOST_CHECK(!(iterCopy != iter));
		++iter;
		BOOST_CHECK(iterCopy != iter);

		auto rIterCopy(rIter);
		BOOST_CHECK(!(rIterCopy != rIter));
		++rIter;
		BOOST_CHECK(rIterCopy != rIter);
	}
BOOST_AUTO_TEST_SUITE_END()