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

    describe("setLight test", () => {
        const model1 = new model();
        const setLightSpy = jest.spyOn(model1, "setLight");

        const trueRule = jest.fn(() => true);

        describe(".setLight", () => {
            test("defines a function", () => {
                expect(typeof model1.setLight).toBe("function");
            });

            test("sets lightStatus when called", () => {
                expect(model1.setLight(true)).toBeUndefined(); // Can be replaced with model1.setLight(true)
                expect(setLightSpy).toHaveBeenLastCalledWith(true);

                setLightSpy.mockClear();
            });
        });
    });

    describe("setDimmer test", () => {
        const model1 = new model();
        const setDimmerSpy = jest.spyOn(model1, "setDimmer");

        describe(".setDimmer", () => {
            test("defines a function", () => {
                expect(typeof model1.setDimmer).toBe("function");
            });

            test("sets dimmer when called", () => {
                expect(model1.setDimmer(10)).toBeUndefined();
                expect(setDimmerSpy).toHaveBeenLastCalledWith(10);

                setDimmerSpy.mockClear();
            });
        });
    });

    //Tove below
    test("defines pendingMessage", () => {
            expect(typeof name.pendingMessage).toBe("boolean");
        }
    )

})