#include <QString>
#include <QtTest>

#include "exceptions/keyerror.h"

#include "core/gameobject.h"
#include "core/player.h"

using namespace Game;

/**
 * @brief The player_tests test the PlayerBase and Player classes
 */
class default_player : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Test setup
     */
    default_player();

private Q_SLOTS:

    // Tests as a PlayerBase

    /**
     * @brief Tests changing the player's name
     * @post Should be changed
     */
    void setName();

    /**
     * @brief Tests adding an object to the player
     * @post Should be added
     */
    void addObject();

    /**
     * @brief Tests adding an list of objects to the player
     * @post Should be added
     */
    void addObjects();

    /**
     * @brief Tests removing an object from the player
     * @post Should be removed
     */
    void removeObject();

    /**
     * @brief Tests removing an object from the player with a \n
     * wrong key
     * @post Should throw a KeyError exception
     */
    void removeObject_exception_keyerror();

    /**
     * @brief Cleanup after remove test
     */
    void removeObject_cleanup();

    /**
     * @brief Tests removing a list of objects from the player
     * @post Should be removed
     */
    void removeObjects();

    /**
     * @brief Tests removing a list of objects from the player
     * @post Should be removed or will not throw an exception
     */
    void removeObjects_verify_no_throw();

    /**
     * @brief Cleanup after remove test
     */
    void removeObjects_cleanup();

    /**
     * @brief Tests removing an object from the player by ID
     * @post Should be removed
     */
    void removeObject_byID();

    /**
     * @brief Tests removing an object from the player by ID \n
     * with the wrong ID
     * @post Should throw a KeyError exception
     */
    void removeObject_byID_exception();

    /**
     * @brief Cleanup after remove test
     */
    void removeObject_byID_cleanup();

    /**
     * @brief Tests removing a list of objects from the player by ID
     * @post Should be removed
     */
    void removeObjects_byID();

    /**
     * @brief Cleanup after remove test
     */
    void removeObjects_byID_cleanup();

    /**
     * @brief Tests removing a list of objects from the player by ID
     * @post Should be removed or will not throw an exception
     */
    void removeObjects_byID_verify_no_throw();


    // Tests as a Player

    /**
     * @brief Tests that a player's color is set up correctly
     * @post Should be set up correctly
     */
    void checkColor();


    /**
     * @brief Test cleanup
     */
    void cleanup();

private:
    const std::string DEFAULT_NAME = "Player";

    const std::vector<std::shared_ptr<Course::GameObject> > BLANK_OBJECTS = {
        std::make_shared<Course::GameObject>(),
        std::make_shared<Course::GameObject>(),
        std::make_shared<Course::GameObject>(),
        std::make_shared<Course::GameObject>(),
        std::make_shared<Course::GameObject>(),

    };

    std::vector<std::shared_ptr<Course::GameObject> > destroyable_objects;

    std::shared_ptr<Player> default_instance;

    bool vectorContainsPtr(std::vector<std::shared_ptr<Course::GameObject> > vec,
                            std::shared_ptr<Course::GameObject> ptr);

};

default_player::default_player()
{
    default_instance = std::make_shared<Player>(DEFAULT_NAME, "red");
}

bool default_player::vectorContainsPtr(
        std::vector<std::shared_ptr<Course::GameObject> > vec,
        std::shared_ptr<Course::GameObject> ptr)
{
    bool found = false;
    for( auto it = vec.begin();
         it != vec.end();
         ++it)
    {
        if(it->get() == ptr.get())
        {
            found = true;
        }
    }

    return found;
}

void default_player::setName()
{
    std::string new_name = "Player two";

    QVERIFY(default_instance->getName() == DEFAULT_NAME);
    default_instance->setName(new_name);
    QVERIFY(default_instance->getName() == new_name);
}

void default_player::addObject()
{
    auto new_object = std::make_shared<Course::GameObject>();

    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObject(new_object);
    QVERIFY(default_instance->getObjects().size() == 1);

    auto objects = default_instance->getObjects();
    QVERIFY(objects.at(0) == new_object);
}

void default_player::addObjects()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    QVERIFY(default_instance->getObjects().size() == BLANK_OBJECTS.size());
}

void default_player::removeObject()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    QVERIFY(default_instance->getObjects().size() == BLANK_OBJECTS.size());

    for( auto it = BLANK_OBJECTS.begin();
         it != BLANK_OBJECTS.end();
         ++it)
    {
        auto size_before_removal = default_instance->getObjects().size();
        auto rm_obj = *it;

        default_instance->removeObject(rm_obj);
        QVERIFY(default_instance->getObjects().size() == size_before_removal-1);

        QVERIFY(not vectorContainsPtr(
                    default_instance->getObjects(),
                    rm_obj));
    }
}

void default_player::removeObject_exception_keyerror()
{
    QVERIFY_EXCEPTION_THROWN(
                default_instance->removeObject(BLANK_OBJECTS.at(0)),
                Course::KeyError
                );
}

void default_player::removeObject_cleanup()
{
    QVERIFY(default_instance->getObjects().empty());
    auto object = std::make_shared<Course::GameObject>();

    default_instance->addObject(object);
    default_instance->addObjects(BLANK_OBJECTS);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() +1);
    object = {};

    default_instance->removeObject(BLANK_OBJECTS.at(0));
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() -1 );
}

void default_player::removeObjects()
{
    QVERIFY(default_instance->getObjects().empty());

    auto rm_objects = {
        BLANK_OBJECTS.at(0),
        BLANK_OBJECTS.at(2),
        BLANK_OBJECTS.at(4)
    };

    default_instance->addObjects(BLANK_OBJECTS);
    QVERIFY(default_instance->getObjects().size() == BLANK_OBJECTS.size());

    default_instance->removeObjects(rm_objects);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() - rm_objects.size());

    for( auto it = rm_objects.begin(); it != rm_objects.end(); ++it)
    {
        QVERIFY( not vectorContainsPtr(default_instance->getObjects(), *it));
    }
}

void default_player::removeObjects_verify_no_throw()
{
    QVERIFY(default_instance->getObjects().empty());

    std::vector<std::shared_ptr<Course::GameObject> > rm_objects = {
        BLANK_OBJECTS.at(0),
        BLANK_OBJECTS.at(2),
        BLANK_OBJECTS.at(4)
    };

    rm_objects.push_back(destroyable_objects.front());

    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->addObjects(destroyable_objects);
    QVERIFY(default_instance->getObjects().size() ==
            (BLANK_OBJECTS.size() + destroyable_objects.size()));

    destroyable_objects = {};
    default_instance->removeObjects(rm_objects);
}

void default_player::removeObjects_cleanup()
{
    QVERIFY(default_instance->getObjects().empty());

    std::vector<std::shared_ptr<Course::GameObject> > rm_objects = {
        BLANK_OBJECTS.at(0),
        BLANK_OBJECTS.at(2),
        BLANK_OBJECTS.at(4)
    };

    rm_objects.push_back(destroyable_objects.front());

    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->addObjects(destroyable_objects);
    QVERIFY(default_instance->getObjects().size() ==
            (BLANK_OBJECTS.size() + destroyable_objects.size()));

    destroyable_objects = {};
    default_instance->removeObjects(rm_objects);

    for( auto it = destroyable_objects.begin();
         it != destroyable_objects.end();
         ++it)
    {
        QVERIFY( not vectorContainsPtr(default_instance->getObjects(),
                                        *it));
    }
}

void default_player::removeObject_byID()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);

    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size());

    default_instance->removeObject(BLANK_OBJECTS.at(0)->ID);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() -1);

    QVERIFY( not vectorContainsPtr(default_instance->getObjects(),
                                    BLANK_OBJECTS.at(0)));

}

void default_player::removeObject_byID_exception()
{
    QVERIFY(default_instance->getObjects().empty());
    QVERIFY_EXCEPTION_THROWN(default_instance->removeObject(0),
                             Course::KeyError);

    Course::ObjectId rm_id = BLANK_OBJECTS.at(0)->ID;
    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->removeObject(rm_id);

    QVERIFY_EXCEPTION_THROWN(default_instance->removeObject(rm_id),
                             Course::KeyError);

}

void default_player::removeObject_byID_cleanup()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->addObjects(destroyable_objects);

    Course::ObjectId rm_id = BLANK_OBJECTS.at(0)->ID;

    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() + destroyable_objects.size());

    destroyable_objects = {};

    default_instance->removeObject(rm_id);

    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() -1);
    for(auto it = destroyable_objects.begin();
        it != destroyable_objects.end();
        ++it)
    {
        QVERIFY(not vectorContainsPtr(default_instance->getObjects(),
                                       *it));
    }
}

void default_player::removeObjects_byID()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size());

    std::vector<Course::ObjectId> rm_vect = {
        BLANK_OBJECTS.at(0)->ID,
        BLANK_OBJECTS.at(2)->ID,
        BLANK_OBJECTS.at(4)->ID
    };

    default_instance->removeObjects(rm_vect);

    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() - rm_vect.size());

    QVERIFY(not vectorContainsPtr(default_instance->getObjects(),
                                   BLANK_OBJECTS.at(0)));
    QVERIFY(not vectorContainsPtr(default_instance->getObjects(),
                                   BLANK_OBJECTS.at(2)));
    QVERIFY(not vectorContainsPtr(default_instance->getObjects(),
                                   BLANK_OBJECTS.at(4)));
}

void default_player::removeObjects_byID_cleanup()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->addObjects(destroyable_objects);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() + destroyable_objects.size());

    std::vector<Course::ObjectId> rm_vect = {
        BLANK_OBJECTS.at(0)->ID,
        BLANK_OBJECTS.at(2)->ID,
        BLANK_OBJECTS.at(4)->ID
    };

    destroyable_objects = {};
    default_instance->removeObjects(rm_vect);

    for( auto it = destroyable_objects.begin();
         it != destroyable_objects.end();
         ++it)
    {
        QVERIFY(not vectorContainsPtr(default_instance->getObjects(), *it));
    }
}

void default_player::removeObjects_byID_verify_no_throw()
{
    QVERIFY(default_instance->getObjects().empty());
    default_instance->addObjects(BLANK_OBJECTS);
    default_instance->addObjects(destroyable_objects);
    QVERIFY(default_instance->getObjects().size() ==
            BLANK_OBJECTS.size() + destroyable_objects.size());


    Course::ObjectId latest_id = destroyable_objects.back()->ID;
    std::vector<Course::ObjectId> rm_vect = {
        latest_id,
        latest_id + 1,
    };

    default_instance->removeObjects(rm_vect);
}

void default_player::checkColor()
{
    QVERIFY(default_instance->getColor() == QString("red"));
}

void default_player::cleanup()
{
    default_instance = std::make_shared<Player>(DEFAULT_NAME, "red");

    destroyable_objects = {
        std::make_shared<Course::GameObject>(),
        std::make_shared<Course::GameObject>()
    };
}


QTEST_APPLESS_MAIN(default_player)

#include "tst_default_player.moc"
