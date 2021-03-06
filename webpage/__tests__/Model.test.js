const model = require('../public/js/Model');

test("Sanity", () => {
    expect(true).toBe(true);
});

describe("Model interface", () => {
    const name = new model();

    test("defines Observer", () => {
        expect(typeof name.observers).toBe("object");
    })
    test("Observer empty list", () => {
        expect(name.observers).toEqual([])
    });

    test("defines currentUser", () => {
        expect(typeof name.currentUser).toBe("object");
    })
    test("currentUser null", () => {
        expect(name.currentUser).toBe(null)
    })

    test("defines currentUsername", () => {
        expect(typeof name.currentUsername).toBe("object");
    })
    test("currentUsername null", () => {
        expect(name.currentUsername).toBe(null)
    })

    test("defines lightOn()", () => {
        expect(typeof name.lightOn).toBe("boolean");
    })
    test('Light off default', () => {
        expect(name.lightOn).toBe(false)
    });

    test("defines dimmer()", () => {
        expect(typeof name.dimmer).toBe("number");
    })
    test("Dimmer default", () => {
        expect(name.dimmer).toBe(25)
    });

    describe("setLight test", () => {
        const model1 = new model();
        const setLightSpy = jest.spyOn(model1, "setLight");

        describe(".setLight", () => {
            test("defines a function", () => {
                expect(typeof model1.setLight).toBe("function");
            });

            test("sets lightStatus when called", () => {
                expect(model1.setLight(true)).toBeUndefined(); // Can be replaced with model1.setLight(true)
                expect(setLightSpy).toHaveBeenLastCalledWith(true);
                expect(model1.lightOn).toBe(true)

                expect(model1.setLight(false)).toBeUndefined();
                expect(setLightSpy).toHaveBeenLastCalledWith(false);
                expect(model1.lightOn).toBe(false)

                setLightSpy.mockClear();
            });
        });
    });

    describe("setDimmer test", () => {
        const model1 = new model();
        const setDimmerSpy = jest.spyOn(model1, "setDimmer");
        let input = 10;
        describe(".setDimmer", () => {
            test("defines a function", () => {
                expect(typeof model1.setDimmer).toBe("function");
            });
            test("sets dimmer when called", () => {
                expect(model1.setDimmer(input)).toBeUndefined();
                expect(setDimmerSpy).toHaveBeenLastCalledWith(input);
                expect(model1.dimmer).toBe(Math.floor(input/100 * 255));
                expect(model1.dimmerShow).toBe(input);

                setDimmerSpy.mockClear();
            });
        });
    });

    describe("Observer", () => {
        const model2 = new model();
        const addObserverSpy = jest.spyOn(model2, "addObserver")
        let callbackToPopulate = "First in que"
        let callbackToTest = "SomethingToTest"
        let expectedObservers = [callbackToPopulate, callbackToTest];

        describe(".addObserver", () => {
            test("define function", () => {
                expect(typeof model2.addObserver).toBe("function");
            });
            test("tests observer", () => {
                model2.addObserver(callbackToPopulate);
                expect(model2.addObserver(callbackToTest)).toBeUndefined();
                expect(addObserverSpy).toHaveBeenLastCalledWith(callbackToTest);
                expect(model2.observers).toStrictEqual(expectedObservers);
                addObserverSpy.mockClear();
            });
        })
    })

    //Tove below
    test("defines pendingMessage", () => {
            expect(typeof name.pendingMessage).toBe("boolean");
        }
    )

    test("morsetext type", () => {
        expect(typeof name.morseText).toBe("string");
        expect.stringMatching(/[0-9a-??A-?? ]+$/);
    })

})