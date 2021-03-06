#include "ecs/inner_join_aspect.hpp"
#include "ecs/entity_component_system.hpp"
#include "test/test.hpp"
#include <set>
#include <tuple>

using namespace gorc;

namespace {

    class mock_health_component {
    public:
        uid(10);
        int value;

        mock_health_component(int value)
            : value(value)
        {
            return;
        }
    };

    class mock_armor_component {
    public:
        uid(20);
        int value;

        mock_armor_component(int value)
            : value(value)
        {
            return;
        }
    };

    class mock_inner_join_aspect : public inner_join_aspect<thing_id,
                                                            mock_health_component,
                                                            mock_armor_component> {
    public:
        std::set<std::tuple<int, int, int>> &values;

        mock_inner_join_aspect(entity_component_system<thing_id> &ecs,
                               std::set<std::tuple<int, int, int>> &values)
            : inner_join_aspect(ecs)
            , values(values)
        {
            return;
        }

        virtual void update(time_delta,
                            thing_id id,
                            mock_health_component &health,
                            mock_armor_component &armor)
        {
            values.emplace(static_cast<int>(id), health.value, armor.value);
        }
    };

    class trivial_inner_join_aspect : public inner_join_aspect<thing_id,
                                                               mock_health_component> {
    public:
        trivial_inner_join_aspect(entity_component_system<thing_id> &ecs)
            : inner_join_aspect(ecs)
        {
            return;
        }

    };

    class inner_join_aspect_fixture : public test::fixture {
    public:
        event_bus bus;
        component_registry<thing_id> cr;
        service_registry services;

        inner_join_aspect_fixture()
        {
            cr.register_component_type<mock_health_component>();
            cr.register_component_type<mock_armor_component>();

            services.add(cr);
            services.add(bus);
        }
    };

}

begin_suite_fixture(inner_join_aspect_test,
                    inner_join_aspect_fixture);

test_case(no_elements)
{
    std::set<std::tuple<int, int, int>> values;

    entity_component_system<thing_id> ecs(services);
    ecs.emplace_aspect<mock_inner_join_aspect>(values);

    ecs.update(std::chrono::seconds(0));

    assert_true(values.empty());
}

test_case(no_matches)
{
    std::set<std::tuple<int, int, int>> values;

    entity_component_system<thing_id> ecs(services);
    ecs.emplace_aspect<mock_inner_join_aspect>(values);

    auto thing0 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing0, 5);

    auto thing1 = ecs.emplace_entity();
    ecs.emplace_component<mock_armor_component>(thing1, 12);

    ecs.update(std::chrono::seconds(0));

    assert_true(values.empty());
}

test_case(find_single)
{
    std::set<std::tuple<int, int, int>> values;

    entity_component_system<thing_id> ecs(services);
    ecs.emplace_aspect<mock_inner_join_aspect>(values);

    auto thing0 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing0, 5);
    ecs.emplace_component<mock_armor_component>(thing0, 10);

    auto thing1 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing1, 15);
    ecs.emplace_component<mock_armor_component>(thing1, 20);

    ecs.update(std::chrono::seconds(0));

    std::set<std::tuple<int, int, int>> expected = {
            std::make_tuple(0, 5, 10),
            std::make_tuple(1, 15, 20)
        };

    assert_range_eq(values, expected);
}

test_case(find_repeats)
{
    std::set<std::tuple<int, int, int>> values;

    entity_component_system<thing_id> ecs(services);
    ecs.emplace_aspect<mock_inner_join_aspect>(values);

    auto thing0 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing0, 5);
    ecs.emplace_component<mock_health_component>(thing0, 10);
    ecs.emplace_component<mock_armor_component>(thing0, 3);

    auto thing1 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing1, 2);
    ecs.emplace_component<mock_armor_component>(thing1, 7);
    ecs.emplace_component<mock_armor_component>(thing1, 14);

    auto thing2 = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(thing2, 11);
    ecs.emplace_component<mock_health_component>(thing2, 22);
    ecs.emplace_component<mock_armor_component>(thing2, 13);
    ecs.emplace_component<mock_armor_component>(thing2, 26);

    ecs.update(std::chrono::seconds(0));

    std::set<std::tuple<int, int, int>> expected = {
            std::make_tuple(0, 5, 3),
            std::make_tuple(0, 10, 3),

            std::make_tuple(1, 2, 7),
            std::make_tuple(1, 2, 14),

            std::make_tuple(2, 11, 13),
            std::make_tuple(2, 11, 26),
            std::make_tuple(2, 22, 13),
            std::make_tuple(2, 22, 26)
        };

    assert_range_eq(values, expected);
}

test_case(has_default_update)
{
    entity_component_system<thing_id> ecs(services);
    ecs.emplace_aspect<trivial_inner_join_aspect>();

    auto tid = ecs.emplace_entity();
    ecs.emplace_component<mock_health_component>(tid, 5);

    ecs.update(std::chrono::seconds(0));
}

end_suite(inner_join_aspect_test);
