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
    })

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
})