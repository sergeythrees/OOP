#include "stdafx.h"
#include "../CMyArray/CMyArray.h" 

using namespace std;

template <typename Ex, typename Fn>
void VerifyException(Fn && fn, const string & expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		BOOST_CHECK_EQUAL(e.what(), expectedDescription);
		return e.what() == expectedDescription;
	});
}

struct ArrayItem
{
	ArrayItem(int data = 0) : data(data)
	{}
	int data;
};

template <typename T = default>
void CheckArraysEquality(CMyArray<T>& a, CMyArray<T>& b)
{
	BOOST_CHECK(a.GetSize() == b.GetSize());
	for (size_t i = 0; i < a.GetSize(); ++i)
	{
		BOOST_CHECK(a[i].data == b[i].data);
	}
}

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};


BOOST_AUTO_TEST_SUITE(CMyArray_)
	BOOST_FIXTURE_TEST_SUITE(after_construction, EmptyStringArray)
		BOOST_AUTO_TEST_SUITE(by_default)
			BOOST_AUTO_TEST_CASE(is_empty)
			{
				BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
			}
			BOOST_AUTO_TEST_CASE(has_0_capacity)
			{
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(after_appending_an_item)
			BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
			{
				arr.Append(ArrayItem());
				BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
				arr.Append(ArrayItem());
				BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
				arr.Append(ArrayItem());
				BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
				arr.Append(ArrayItem());
				BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			}
			BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
			{
				arr.Append(1);
				BOOST_CHECK_EQUAL(arr.GetBack().data, 1);
				arr.Append(2);
				BOOST_CHECK_EQUAL(arr.GetBack().data, 2);
				arr.Append(3);
				BOOST_CHECK_EQUAL(arr.GetBack().data, 3);
				arr.Append(4);
				BOOST_CHECK_EQUAL(arr.GetBack().data, 4);
			}
		BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE_END()

		struct FilledArray
		{
			CMyArray<ArrayItem> arr;
			FilledArray()
				:arr(CMyArray<ArrayItem>())
			{
				for (auto i = 0; i <= 6; ++i)
				{
					arr.Append(i);
				}
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_filled, FilledArray)
			BOOST_AUTO_TEST_SUITE(after_copy_construction)
				BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
				{
					BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

					auto copy(arr);
					BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
					BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(move_construction)
				BOOST_AUTO_TEST_CASE(get_original_array_data_and_makes_its_empty)
				{
					auto arrBackup(arr);
					BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

					auto movedArray(move(arr));

					CheckArraysEquality(movedArray, arrBackup);
					BOOST_CHECK(arr.GetSize() == 0);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(has_indexed_access)
				BOOST_AUTO_TEST_CASE(that_returns_reference_to_appropriate_element)
				{
					BOOST_CHECK_EQUAL(arr[4].data, 4);
					arr[4].data = 365;
					BOOST_CHECK_EQUAL(arr[4].data, 365);
				}
				BOOST_AUTO_TEST_CASE(and_should_throw_out_of_range_if_index_exceeds_array_size)
				{
					BOOST_CHECK_THROW(arr[10], std::out_of_range);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(has_resize_method)
				BOOST_AUTO_TEST_CASE(that_can_increases_or_decreases_array_size)
				{
					arr.Resize(2);
					BOOST_CHECK(arr.GetSize() == 2);

					arr.Resize(10);
					BOOST_CHECK(arr.GetSize() == 10);
					for (size_t i = 2; i < 9; ++i)
					{
						BOOST_CHECK(arr[i].data == 0);
					}
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_CASE(can_be_cleared)
			{
				arr.Clear();
				BOOST_CHECK(arr.GetSize() == 0);
				BOOST_CHECK_THROW(arr[0], std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(can_be_assigned)
			{
				CMyArray<ArrayItem> copiedArray;
				copiedArray = arr;
			
				CheckArraysEquality(copiedArray, arr);
			}
			BOOST_AUTO_TEST_CASE(can_be_moved)
			{
				CMyArray<ArrayItem> arrBackup(arr);

				CMyArray<ArrayItem> movedArray;
				movedArray = move(arr);

				CheckArraysEquality(movedArray, arrBackup);
				BOOST_CHECK(arr.GetSize() == 0);
			}
			BOOST_AUTO_TEST_CASE(can_be_correctly_assigned_or_moved_to_itself)
			{
				auto arrBackup = arr;
				auto oldCapacity = arr.GetCapacity();

				arr = arr;
				BOOST_CHECK_EQUAL(oldCapacity, arr.GetCapacity());
				CheckArraysEquality(arrBackup, arr);

				arr = move(arr);
				BOOST_CHECK_EQUAL(oldCapacity, arr.GetCapacity());
				CheckArraysEquality(arrBackup, arr);
			}

			BOOST_AUTO_TEST_SUITE(has_a_iterative_access)
				BOOST_AUTO_TEST_CASE(with_the_begin_method)
				{
					auto it = arr.begin();
					BOOST_CHECK_EQUAL((*it).data, 0);
					++it;
					++it;
					BOOST_CHECK_EQUAL((*it).data, 2);
					--it;
					BOOST_CHECK_EQUAL((*it).data, 1);
				}
				BOOST_AUTO_TEST_CASE(with_the_end_method)
				{
					auto it = arr.end();
					--it;
					BOOST_CHECK_EQUAL((*it).data, 6);
					--it;
					--it;
					BOOST_CHECK_EQUAL((*it).data, 4);
					++it;
					BOOST_CHECK_EQUAL((*it).data, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE(has_a_recursive_iterative_access)
				BOOST_AUTO_TEST_CASE(with_the_rbegin_method)
				{
					auto it = arr.rbegin();
					BOOST_CHECK_EQUAL((*it).data, 6);
					++it;
					++it;
					BOOST_CHECK_EQUAL((*it).data, 4);
					--it;
					BOOST_CHECK_EQUAL((*it).data, 5);
				}
				BOOST_AUTO_TEST_CASE(with_the_rend_method)
				{
					auto it = arr.rend();
					--it;
					BOOST_CHECK_EQUAL((*it).data, 0);
					--it;
					--it;
					BOOST_CHECK_EQUAL((*it).data, 2);
					++it;
					BOOST_CHECK_EQUAL((*it).data, 1);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()

		struct throwable
		{
			class IamTheDanger
			{
			public:
				IamTheDanger()
					: data(""),
					m_isThrowingEnabled(false)
				{
					throw exception("default constructor");
				};
				IamTheDanger(string data, bool isThrowingEnabled)
					:data(data),
					m_isThrowingEnabled(isThrowingEnabled) {}

				IamTheDanger(const IamTheDanger& copy)
					:data(copy.data),
					m_isThrowingEnabled(copy.m_isThrowingEnabled)
				{
					if (copy.m_isThrowingEnabled)
						throw exception("from copy constructor");
				}
				void EnableThrowing(bool enable)
				{
					m_isThrowingEnabled = enable;
				}

				string data;
			private:
				bool m_isThrowingEnabled;
			};

			CMyArray<IamTheDanger> original;
			CMyArray<IamTheDanger> backup;
			throwable()
			{
				original.Append(IamTheDanger("one", false));
				original.Append(IamTheDanger("two", false));
				original.Append(IamTheDanger("three", false));
				original.Append(IamTheDanger("boom", false));
				original[3].EnableThrowing(true);
				backup.Append(IamTheDanger("one", false));
				backup.Append(IamTheDanger("two", false));
				backup.Append(IamTheDanger("three", false));
				backup.Append(IamTheDanger("boom", false));
			}
		};
		BOOST_FIXTURE_TEST_SUITE(should_use_commit_or_rollback_semantics, throwable)
			BOOST_AUTO_TEST_CASE(when_assigning)
			{
				CMyArray<IamTheDanger> forCopy;
				forCopy.Append(IamTheDanger("", false));
				forCopy[0].EnableThrowing(true);

				VerifyException<exception>([&](){original = forCopy;},	
					"from copy constructor");
				CheckArraysEquality(original, backup);
				BOOST_CHECK(original.GetCapacity() == backup.GetCapacity());
			}
			BOOST_AUTO_TEST_CASE(in_Resize_method)
			{
				VerifyException<exception>([&]() {original.Resize(20); },
					"default constructor");
				CheckArraysEquality(original, backup);
				BOOST_CHECK(original.GetCapacity() == backup.GetCapacity());
			}
			BOOST_AUTO_TEST_CASE(in_Append_method)
			{
				VerifyException<exception>([&]() {original.Append(IamTheDanger("boom", true)); },
					"from copy constructor");
				CheckArraysEquality(original, backup);
				BOOST_CHECK(original.GetCapacity() == backup.GetCapacity());
			}

			BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()