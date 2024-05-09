#include <gtest/gtest.h>
#include <pumba/pumba.hpp>


struct MyTraits {
    using HashType = int;

    static HashType GetHash(const std::string& node) {
        return std::hash<std::string>{}(node);
    }

    static std::vector<HashType> Replicate(const std::string& node, std::size_t replicas) {
        std::vector<HashType> result;
        result.reserve(replicas);

        for (int i = 0; i < replicas; ++i) {
            result.emplace_back(GetHash(node + "#" + std::to_string(i)));
        }

        return result;
    }
};

using Router = pumba::ConsistentHashingRouter<std::string, MyTraits>;

TEST(TestRouter, Construction)
{
    Router router(/*replicas=*/3);
    ASSERT_EQ(router.Replicas(), 3);
    ASSERT_TRUE(router.Empty());
    ASSERT_EQ(router.PhysicalNodes(), 0);
}

TEST(TestRouter, Insertion)
{
    Router router(/*replicas=*/3);
    ASSERT_EQ(router.Replicas(), 3);
    ASSERT_TRUE(router.Empty());
    ASSERT_EQ(router.PhysicalNodes(), 0);

    router.EmplaceNode("Node");
    ASSERT_EQ(router.PhysicalNodes(), 1);
    ASSERT_FALSE(router.Empty());

    for (int i = 0; i < 100; ++i) {
        std::string node = router.SelectNode("Client" + std::to_string(i));
        ASSERT_EQ(node, "Node");
    }

}


TEST(TestRouter, erase)
{
    Router router(/*replicas=*/3);
    router.EmplaceNode("Node");
    router.EmplaceNode("Another one");

    ASSERT_NO_THROW(router.EraseNode("Node"));
    ASSERT_NO_THROW(router.EraseNode("Another one"));

    ASSERT_TRUE(router.Empty());
}



