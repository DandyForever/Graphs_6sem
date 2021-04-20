#include "tests.h"

void TestFloyd () {
    {
        Graph g;
        auto path = g.floyd();
        Assert(path.empty(), "Empty Graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        auto path = g.floyd();
        std::map <int, int> line1 = {{1, 0}, {2, 1e9}};
        std::map <int, int> line2 = {{1, 1e9}, {2, 0}};
        std::map <int, map <int, int>> ans = {{1, line1}, {2, line2}};
        AssertEqual(path, ans, "No edge graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        auto path = g.floyd();
        std::map <int, map <int, int>> ans = {{1, {{1, 0}}}};
        AssertEqual(path, ans, "Single vertex graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_edge(1, 2, 1);
        g.add_edge(1, 3, 6);
        g.add_edge(2, 3, 4);
        g.add_edge(2, 4, 1);
        g.add_edge(4, 3, 1);

        auto path = g.floyd();
        std::map <int, int> line1 = {{1, 0}, {2, 1}, {3, 3}, {4, 2}};
        std::map <int, int> line2 = {{1, 1e9}, {2, 0}, {3, 2}, {4, 1}};
        std::map <int, int> line3 = {{1, 1e9}, {2, 1e9}, {3, 0}, {4, 1e9}};
        std::map <int, int> line4 = {{1, 1e9}, {2, 1e9}, {3, 1}, {4, 0}};
        std::map <int, map <int, int>> ans = {{1, line1}, {2, line2}, {3, line3}, {4, line4}};
        AssertEqual(path, ans, "Working test 1");
    }
    {
        Graph g;
        g.add_vertex(0);
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_edge(0, 1, 5);
        g.add_edge(0, 3, 10);
        g.add_edge(1, 2, 3);
        g.add_edge(2, 3, 1);

        auto path = g.floyd();
        std::map <int, int> line1 = {{0, 0}, {1, 5}, {2, 8}, {3, 9}};
        std::map <int, int> line2 = {{0, 1e9}, {1, 0}, {2, 3}, {3, 4}};
        std::map <int, int> line3 = {{0, 1e9}, {1, 1e9}, {2, 0}, {3, 1}};
        std::map <int, int> line4 = {{0, 1e9}, {1, 1e9}, {2, 1e9}, {3, 0}};
        std::map <int, map <int, int>> ans = {{0, line1}, {1, line2}, {2, line3}, {3, line4}};
        AssertEqual(path, ans, "Working test 2");
    }
};

void TestHardComponents () {
    {
        Graph g;
        auto components = g.get_components();
        Assert(components.empty(), "Empty Graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        std::set <std::set <int>> ans = {{1}};
        AssertEqual(g.get_components(), ans, "Single vertex graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        std::set <std::set <int>> ans = {{1}, {2}};
        AssertEqual(g.get_components(), ans, "No edge graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_vertex(5);
        g.add_edge(1, 2, 1);
        g.add_edge(1, 3, 1);
        g.add_edge(2, 4, 1);
        g.add_edge(3, 5, 1);
        g.add_edge(4, 5, 1);
        g.add_edge(5, 2, 1);

        std::set <std::set <int>> ans = {{1}, {2, 4, 5}, {3}};
        AssertEqual(g.get_components(), ans, "Working test");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_vertex(5);
        g.add_edge(1, 2, 1);
        g.add_edge(1, 3, 1);
        g.add_edge(1, 4, 1);
        g.add_edge(1, 5, 1);

        std::set <std::set <int>> ans = {{1}, {2}, {3}, {4}, {5}};
        AssertEqual(g.get_components(), ans, "No hard components graph");
    }
    {
        Graph g;
        g.add_vertex(0);
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_edge(0, 2, 1);
        g.add_edge(1, 0, 1);
        g.add_edge(2, 1, 1);
        g.add_edge(3, 1, 1);
        g.add_edge(3, 4, 1);
        g.add_edge(4, 3, 1);

        std::set <std::set <int>> ans = {{0, 1, 2}, {3, 4}};
        AssertEqual(g.get_components(), ans, "2 components graph");
    }
    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_edge(1, 2, 1);
        g.add_edge(1, 3, 1);
        g.add_edge(2, 1, 1);
        g.add_edge(2, 3, 1);
        g.add_edge(3, 1, 1);
        g.add_edge(3, 2, 1);
        std::set <std::set <int>> ans = {{1, 2, 3}};
        AssertEqual(g.get_components(), ans, "Indirected graph");
    }
}

void TestTwoThreeTree () {
    {
        TwoThreeTree tree{};
        Assert(!tree.search(1), "Empty tree");
    }
    {
        TwoThreeTree tree{};
        Assert(!tree.search(1), "Insert test pt 1");
        tree.insert(1);
        Assert(tree.search(1), "Insert test pt 2");
    }
    {
        TwoThreeTree tree{};
        Assert(!tree.search(1), "Remove test pt 1");
        tree.insert(1);
        Assert(tree.search(1), "Remove test pt 2");
        tree.remove(1);
        Assert(!tree.search(1), "Remove test pt 3");
    }
    {
        TwoThreeTree tree{};
        tree.insert(1);
        Assert(tree.search(1), "Tick Tock element pt1");
        tree.remove(1);
        Assert(!tree.search(1), "Tick Tock element pt2");
        tree.insert(1);
        Assert(tree.search(1), "Tick Tock element pt3");
        tree.remove(1);
        Assert(!tree.search(1), "Tick Tock element pt4");
    }
    {
        TwoThreeTree tree{};
        tree.insert(5);
        tree.insert(1);
        tree.insert(12);
        tree.insert(100);
        tree.insert(50);
        tree.insert(3);
        tree.remove(5);
        Assert(!tree.search(5), "Big tree tick tock element pt 1");
        tree.insert(5);
        Assert(tree.search(5), "Big tree tick tock element pt 2");
        tree.remove(5);
        Assert(!tree.search(5), "Big tree tick tock element pt 3");
        Assert(tree.search(1), "Big tree tick tock element pt 4");
        Assert(tree.search(12), "Big tree tick tock element pt 5");
        Assert(tree.search(100), "Big tree tick tock element pt 6");
        Assert(tree.search(50), "Big tree tick tock element pt 7");
        Assert(tree.search(3), "Big tree tick tock element pt 8");
    }
    {
        TwoThreeTree tree{};
        tree.insert(5);
        tree.insert(50);
        tree.insert(12);
        tree.insert(45);
        tree.insert(56);
        tree.insert(15);
        tree.insert(3);
        tree.insert(1);
        tree.insert(6);
        tree.insert(10);
        tree.remove(5);
        tree.remove(12);
        tree.remove(5);
        tree.remove(50);
        tree.remove(56);
        tree.remove(3);
        tree.remove(15);
        tree.remove(45);
        Assert(!tree.search(5), "Hard working test pt 1");
        Assert(!tree.search(50), "Hard working test pt 2");
        Assert(!tree.search(12), "Hard working test pt 3");
        Assert(!tree.search(45), "Hard working test pt 4");
        Assert(!tree.search(56), "Hard working test pt 5");
        Assert(!tree.search(15), "Hard working test pt 6");
        Assert(!tree.search(3), "Hard working test pt 7");
        Assert(tree.search(1), "Hard working test pt 8");
        Assert(tree.search(6), "Hard working test pt 9");
        Assert(tree.search(10), "Hard working test pt 10");
    }
}

void TestAll () {
    TestRunner tr;
    tr.RunTest(TestFloyd, "Floyd");
    tr.RunTest(TestHardComponents, "Hard Components");
    tr.RunTest(TestTwoThreeTree, "2-3 tree");
}